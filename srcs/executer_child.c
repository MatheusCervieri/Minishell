/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:50:34 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/30 10:38:10 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd(char **paths, char *cmd)
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
	return (cmd);
}

static void	sub_dup2(int read_fd, int write_fd)
{
	dup2(read_fd, STDIN_FILENO);
	dup2(write_fd, STDOUT_FILENO);
}

void	handle_dup(t_pipex *data)
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
		if(execve(data.cmd, data.cmd_args, envp) < 0)
			perror(data.cmd);
		exit(0);
}
