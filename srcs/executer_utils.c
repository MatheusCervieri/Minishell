/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:30:08 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/01 12:46:41 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
		if (!envp)
			break ;
	}
	return (*envp + 5);
}

void	init_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_nmbs - 1)
	{
		if (pipe(data->pipe + (2 * i)) < 0)
			parent_close(data, "Failed to pipe\n", 4);
		i++;
	}
}

void	close_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < (data->pipe_nmbs))
	{
		close(data->pipe[i]);
		i++;
	}
	data->success = 1;
}

void	put_infile_fd(t_pipex *data, char *infile_path)
{
	int	pid;

	if (ft_strncmp(infile_path, "STDIN_FILENO", 13) == 0)
		data->infile_exists = 0;
	else
		data->infile_exists = 1;
	if (data->infile_exists != 0 && data->here_doc == 0)
	{
		data->infile = open(infile_path, O_RDONLY);
		if (data->infile < 0)
			msg_error("Invalid infile\n", 7);
	}
	else if (data->here_doc == 1)
	{
		pid = fork();
		if (pid == 0)
			here_doc(data->limiter, data);
		waitpid(pid, NULL, 0);
		data->infile = open(".heredoc_tmp", O_RDONLY);
		if (data->infile < 0)
			msg_error("Can`t open here_doc file\n", 7);
	}
	else
		data->infile = 0;
}

void	put_outfile_fd(t_pipex *data, char *outfile_path)
{
	if (!(ft_strncmp(outfile_path, "STDOUT_FILENO", 14) == 0))
	{
		if (data->append == 1)
			data->outfile = open(outfile_path, O_WRONLY | O_CREAT | O_APPEND,
					0000644);
		else
		{
		data->outfile = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC,
					0000644);
		}
		if (data->outfile < 0)
		{
			close(data->infile);
			msg_error("Bad Permission Outfile\n", 8);
		}
	}
	else
	{
		data->outfile = 1;
	}
}
