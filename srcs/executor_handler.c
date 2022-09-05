/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:16:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/05 18:17:49 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_data_executor(t_pipex *data, char *envp[])
{
	char	*tmp;

	data->cmd_nmbs = g_cmd_table->n_of_cmds;
	data->pipe_nmbs = 2 * (data->cmd_nmbs - 1);
	data->idx = 0;
	data->success = 0;
	data->path = 1;
	data->here_doc = g_cmd_table->here_doc;
	data->append = g_cmd_table->append;
	data->limiter = g_cmd_table->limiter;
	if (put_infile_fd(data, g_cmd_table->infile, envp) > 0)
		return (1);
	if(put_outfile_fd(data, g_cmd_table->outfile) > 0)
		return (1);
	data->pipe = (int *)malloc(sizeof(int) * data->pipe_nmbs);
	if (!data->pipe)
		close_io_exit(data, "Failed to malloc\n", 2);
	tmp = find_path(envp);
	if (!tmp)
		data->path = 0;
	else
	{	
		data->cmd_paths = ft_split(tmp, ':');
		if (!data->cmd_paths)
			pipe_free(data, "Failed to malloc\n", 3);
	}
	init_pipes(data);
	return (0);
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
		if (g_cmd_table->status != 130)
			g_cmd_table->status = WEXITSTATUS(status[i]);
		i++;
	}
	free(status);
}

int	execute(t_pipex *data, char **envp)
{
	int	rtn;

	rtn = 0;
	if (is_builtin(data->cmd) == 1 && data->cmd_nmbs == 1)
		rtn = execute_builtin(data, data->cmd, data->cmd_args, envp);
	else
	{
		signal(SIGINT, ctrlc_child_handler);
		data->pids[data->idx] = fork();
		if (data->pids[data->idx] == 0)
		{
			child_pipes(data, envp);
		}
	}
	return (rtn);
}

int	executor_loop(t_pipex *data, char **envp)
{
	int	rtn;

	while (data->idx < data->cmd_nmbs)
	{
		if (data->idx != 0)
		{
			free_split_line(data->cmd_args);
			free(data->cmd);
		}
		data->cmd_args = ft_split(g_cmd_table->table[data->idx],
				' ');
		if (data->cmd_args[0][0] != '/')
			data->cmd = get_cmd(data->cmd_paths, data->cmd_args[0], data);
		else
			data->cmd = ft_strdup(data->cmd_args[0]);
		rtn = execute(data, envp);
		data->idx++;
	}
	return (rtn);
}

void	executor_handler(void)
{
	t_pipex	data;
	char	**envp;
	int		i;
	int		rtn;

	envp = convert_list_to_char();
	g_cmd_table->here_doc_execute = 1;
	if (g_cmd_table->here_doc_execute == 1)
	{
		if (init_data_executor(&data, envp))
		{
			free_split_line(envp);
			return ;
		}
		data.pids = malloc(sizeof(int) * data.cmd_nmbs);
		rtn = executor_loop(&data, envp);
		close_pipes(&data);
		if (!(is_builtin(data.cmd) == 1 && data.cmd_nmbs == 1))
			wait_pids(&data);
		delete_data(&data, envp);
		if (rtn == 42)
		{
			free_global();
			clear_memory();
			exit(0);
		}		
	}
}
