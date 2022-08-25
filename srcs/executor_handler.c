/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:16:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/25 11:07:42 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//trouxe essas duas funções para ca para manter estatica.

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static void	init_pipes(t_pipex *data)
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

//mudei
void	init_data_executor(t_pipex *data, char *envp[])
{
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

//mudei
void	executor_handler(t_cmd_table *table, char **envp)
{
	t_pipex	data;
	int		status;

	data.cmd_nmbs = table->n_of_cmds;
	data.here_doc = table->here_doc;
	data.append = table->append;
	data.limiter = table->limiter;
	data.infile = open(table->infile, O_RDONLY);
	data.outfile = open(table->outfile, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	init_data_executor(&data, envp);
	while (data.idx < data.cmd_nmbs)
	{
		child(data, table->table, envp);
		data.idx++;
	}
	close_pipes(&data);
	waitpid(-1, &status, 0);
	parent_close(&data, "success", 0);
	g_cmd_table->status = WEXITSTATUS(status);
}
