/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:16:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/23 21:22:40 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_infile_fd(t_pipex *data, char *infile_path)
{
	if(ft_strncmp(infile_path, "STDIN_FILENO", 13) == 0)
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
		here_doc(data->limiter, data);
	}
	else
	{
		data->infile = 0;
	}
}

void	put_outfile_fd(t_pipex *data, char *outfile_path)
{
	if(ft_strncmp(outfile_path, "STDOUT_FILENO", 14) == 0)
		data->outfile_exists = 0;
	else
		data->outfile_exists = 1;	
	if (data->outfile_exists != 0)
	{
		if (data->append == 1)
			data->outfile = open(outfile_path, O_WRONLY | O_CREAT | O_APPEND,
					0000644);
		else
			data->outfile = open(outfile_path, O_CREAT | O_RDWR | O_TRUNC,
					0000644);
		if (data->outfile < 0)
		{
			close(data->infile);
			msg_error("Invalid Outfile\n", 8);
		}
	}
	else
	{
		data->outfile = 1;
	}
}

void	init_data_executor(t_pipex *data, char *envp[])
{
	data->cmd_nmbs = g_cmd_table->n_of_cmds;
	data->pipe_nmbs = 2 * (data->cmd_nmbs - 1);
	data->idx = 0;
	data->success = 0;
	data->pipe = (int *)malloc(sizeof(int) * data->pipe_nmbs);
	if (!data->pipe)
		close_io_exit(data, "Failed to malloc\n", 2);
	data->cmd_paths = ft_split(find_path(envp), ':');
	if (!data->cmd_paths)
		pipe_free(data, "failed to malloc\n", 3);
	init_pipes(data);
}

void	executor_handler(void)
{
	t_pipex	data;
	int		status;
	char	**envp;


	
	envp = convert_list_to_char(g_cmd_table->envp);
	data.infile_exists = g_cmd_table->infile_exists;
	data.outfile_exists = g_cmd_table->outfile_exists;
	data.here_doc = g_cmd_table->here_doc;
	data.append = g_cmd_table->append;
	data.limiter = g_cmd_table->limiter;
	put_infile_fd(&data, g_cmd_table->infile);
	put_outfile_fd(&data, g_cmd_table->outfile);
	init_data_executor(&data, envp);
	while (data.idx < data.cmd_nmbs)
	{
		child(data, envp);
		data.idx++;
	}
	close_pipes(&data);
	waitpid(-1, &status, 0);
	parent_close(&data, "success", 0);
	g_cmd_table->last_status = WEXITSTATUS(status);
}
