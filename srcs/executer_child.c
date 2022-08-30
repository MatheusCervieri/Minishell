/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:50:34 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/29 21:42:24 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (is_builtin(cmd) == 1)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void	sub_dup2(int read_fd, int write_fd)
{
	dup2(read_fd, STDIN_FILENO);
	dup2(write_fd, STDOUT_FILENO);
}

static void	handle_dup(t_pipex *data)
{
	if (data->idx == 0)
	{
		dup2(data->infile, STDIN_FILENO);
		dup2(data->pipe[1], STDOUT_FILENO);
	}
	else if (data->idx == data->cmd_nmbs - 1)
	{
		dup2(data->pipe[(2 * data->idx) - 2], STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
	}
	else
		sub_dup2(data->pipe[(2 * data->idx) - 2], \
					data->pipe[(2 * data->idx) + 1]);
}

int is_directory(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	return(0);
}


void convert_list_to_fd(t_pipex data)
{
	t_list *aux;
	aux = g_cmd_table->envp;
	while(aux)
	{
		ft_putstr_fd(aux->content, data.fd_bi[1]);
		ft_putstr_fd("\n", data.fd_bi[1]);
		aux = aux->next;
	}
	close(data.fd_bi[0]);
	close(data.fd_bi[1]);
}

void convert_list_to_fd_fds(int fd[2])
{
	t_list *aux;
	aux = g_cmd_table->envp;
	while(aux)
	{
		ft_putstr_fd(aux->content, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		aux = aux->next;
	}
	close(fd[0]);
	close(fd[1]);
}

void	child(t_pipex data, char **envp)
{
		if (data.cmd_nmbs != 1)
			handle_dup(&data);
		else
		{
			dup2(data.infile, STDIN_FILENO);
			dup2(data.outfile, STDOUT_FILENO);
		}
		close_pipes(&data);
		data.cmd_args = ft_split(g_cmd_table->table[data.idx],
				' ');
		if(is_directory(data.cmd_args[0]) == 0)
			data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
		else
			data.cmd = data.cmd_args[0];
		if (!data.cmd)
			free_cmd(&data);
		
		if (is_builtin(data.cmd) == 1)
		{
			if(ft_strncmp(data.cmd, "exit", 5) == 0)
			{
			convert_list_to_fd(data);
			close(data.fd_bi[0]);
			close(data.fd_bi[1]);
			}
			execute_builtin(data.cmd, data.cmd_args, envp, data.pid, data.fd_bi);
		}
		else
		{
			convert_list_to_fd(data);
			close(data.fd_bi[0]);
			close(data.fd_bi[1]);
			execve(data.cmd, data.cmd_args, envp);
		}
		exit(0);
}
