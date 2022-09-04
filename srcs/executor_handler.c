/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:16:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/03 22:14:36 by ghenaut-         ###   ########.fr       */
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
		pipe_free(data, "Failed to malloc\n", 3);
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

int	executor_loop(t_pipex *data, char **envp)
{
	int	rtn;
	int	i;

	rtn = 0; 
	while (data->idx < data->cmd_nmbs)
	{
		if (data->idx != 0)
		{
			i = 0;
			while (data->cmd_args[i])
			{
				free(data->cmd_args[i]);
				i++;
			}
			free(data->cmd_args);
			free(data->cmd);
		}
		data->cmd_args = ft_split(g_cmd_table->table[data->idx],
				' ');
		if (is_directory(data->cmd_args[0]) == 0)
			data->cmd = get_cmd(data->cmd_paths, data->cmd_args[0]);
		else
			data->cmd = ft_strdup(data->cmd_args[0]);
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
	data->idx++;
	}
	return (rtn);
}

void	delete_data(t_pipex *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	parent_close(data, "success", 0);
	free(data->pids);
	i = 0;
	while (data->cmd_args[i])
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd);
	free(data->cmd_args);
}


void	executor_handler(void)
{
	t_pipex	data;
	char	**envp;
	int		i;
	int		rtn;

	envp = convert_list_to_char();
	g_cmd_table->here_doc_execute = 1;
	data.here_doc = g_cmd_table->here_doc;
	data.append = g_cmd_table->append;
	data.limiter = g_cmd_table->limiter;
	put_infile_fd(&data, g_cmd_table->infile, envp);
	put_outfile_fd(&data, g_cmd_table->outfile);
	if (g_cmd_table->here_doc_execute == 1)
	{
		init_data_executor(&data, envp);
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
