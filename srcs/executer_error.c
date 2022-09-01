/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:14:57 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/01 16:10:39 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msg_error(char *error, int exit_code)
{
	write(2, error, ft_strlen(error));
	g_cmd_table->status = exit_code;
}

void	close_io_exit(t_pipex *data, char *error, int exit_code)
{
	if (data->infile != 0)
		close(data->infile);
	if (data->outfile != 1)
		close(data->outfile);
	if (data->here_doc)
		unlink(".heredoc_tmp");
	if (!data->success)
		msg_error(error, exit_code);
}

void	pipe_free(t_pipex *data, char *error, int exit_code)
{
	free(data->pipe);
	
	close_io_exit(data, error, exit_code);
}

void	parent_close(t_pipex *data, char *error, int exit_code)
{
	int	i;

	i = 0;
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
	pipe_free(data, error, exit_code);
}

void	free_cmd(t_pipex *data)
{
	int		i;

	i = 0;
	while (data->cmd_args[i])
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd_args);
	free(data->cmd);
	perror("Command not found");
}
