/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:30:08 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/05 18:16:15 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
	{
		i++;
		if (!envp[i])
			return (NULL);
	}
	return (envp[i] + 5);
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

int	put_infile_fd(t_pipex *data, char *infile_path, char **envp)
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
		{
			perror(infile_path);
			return (1);
		}
	}
	else if (data->here_doc == 1)
	{
		pid = fork();
		if (pid == 0)
			here_doc(data->limiter, data, envp);
		waitpid(pid, NULL, 0);
		data->infile = open(".heredoc_tmp", O_RDONLY);
		if (data->infile < 0)
			msg_error("Can`t open here_doc file\n", 7);
	}
	else
		data->infile = 0;
}

int	put_outfile_fd(t_pipex *data, char *outfile_path)
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
			if (data->infile > 0)
				close(data->infile);
			perror(outfile_path);
			return (1);
		}
	}
	else
		data->outfile = 1;
	return (0);
}
