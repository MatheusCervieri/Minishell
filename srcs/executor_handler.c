/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:16:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/31 12:18:20 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	wait_pids(t_pipex *data)
{
	int	i;
	int	*status;

	status = malloc(sizeof(int) * data->cmd_nmbs);
	i = 0;
	while (i < data->cmd_nmbs)
	{
		waitpid(data->pids[i], &status[i], 0);
		g_cmd_table->status = WEXITSTATUS(status[i]);
		i++;
	}
	free(status);
}

int	is_directory(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	return (0);
}

void	executor_loop(t_pipex *data, char **envp)
{
	while (data->idx < data->cmd_nmbs)
	{
		data->cmd_args = ft_split(g_cmd_table->table[data->idx],
				' ');
		if (is_directory(data->cmd_args[0]) == 0)
			data->cmd = get_cmd(data->cmd_paths, data->cmd_args[0]);
		else
			data->cmd = data->cmd_args[0];
		if (is_builtin(data->cmd) == 1)
			execute_builtin(data, data->cmd, data->cmd_args, envp);
		else
		{
			data->pids[data->idx] = fork();
			if (data->pids[data->idx] == 0)
			{
				child(data, envp);
			}
		}
	data->idx++;
	}
}

void	executor_handler(void)
{
	t_pipex	data;
	int		pipe_stdin;
	char	**envp;

	envp = convert_list_to_char();
	data.here_doc = g_cmd_table->here_doc;
	data.append = g_cmd_table->append;
	data.limiter = g_cmd_table->limiter;
	put_infile_fd(&data, g_cmd_table->infile);
	put_outfile_fd(&data, g_cmd_table->outfile);
	init_data_executor(&data, envp);
	data.pids = malloc(sizeof(int) * data.cmd_nmbs);
	executor_loop(&data, envp);
	close_pipes(&data);
	wait_pids(&data);
	free(data.pids);
	parent_close(&data, "success", 0);
}
