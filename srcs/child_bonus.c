/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:50:34 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/18 17:09:07 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

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


/*
	cmd args!!!
	"wc"
	"l"
	ex2:
	"ls"
	"a"
	"wc -l"
	char[0][0] = "wc";
	char[0][1] = "-l";
	char[0][1][1] = '1';
*/


void	child(t_pipex data, char **envp)
{
	data.pid = fork();
	if (!data.pid)
	{
		handle_dup(&data);
		close_pipes(&data);
		data.cmd_args = ft_split(g_cmd_table.comands_string[data.idx], ' '); //data.heredoc não muda nada se a gente já tiver os comandos.
		data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
		if (!data.cmd)
			free_cmd(&data);
		
		execve(data.cmd, data.cmd_args, envp);
	}
}
