/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:16:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/29 20:48:15 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_infile_fd(t_pipex *data, char *infile_path)
{
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
		here_doc(data->limiter, data);
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

void wait_pids(t_pipex *data)
{
	int i;
	int *status;

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
void convert_fd_to_list(t_pipex data)
{
	/*
	char *node_content;
	t_list *lst;
	node_content = get_next_line(data.fd_bi[0]);
	lst = ft_lstnew(node_content);
	printf("%s\n", (char *)lst->content);
	while (node_content)
	{
		node_content = get_next_line(data.fd_bi[0]);
		ft_lstadd_back(&lst, ft_lstnew(node_content));
		ft_putstr_fd("WTF \n", 2);
	}
	ft_putstr_fd(":(\n", 2);
	while(lst)
	{
		printf("%s", (char *) lst->content);
		lst = lst->next;
	}
	*/
	char *buf = malloc(sizeof(char) * 100);
	char *final_string;
	final_string = ft_strdup("");
	int read_rn;
	read_rn = 99;
	while (read_rn >= 99)
	{
		read_rn = read(data.fd_bi[0], buf, 99);
		if(buf != NULL)
			final_string = ft_strjoin(final_string, buf);	
	}
	//printf("\n\n%s\n\n", final_string);
	//ft_putstr_fd("\n", 1);
}

void	executor_handler(void)
{
	t_pipex	data;
	int		pipe_stdin;
	char	**envp;

	pipe(data.fd_bi);
	pipe_stdin = dup(STDIN_FILENO);
	envp = convert_list_to_char();
	data.here_doc = g_cmd_table->here_doc;
	data.append = g_cmd_table->append;
	data.limiter = g_cmd_table->limiter;
	put_infile_fd(&data, g_cmd_table->infile);
	put_outfile_fd(&data, g_cmd_table->outfile);
	init_data_executor(&data, envp);
	data.pids = malloc(sizeof(int) * data.cmd_nmbs);
	while (data.idx < data.cmd_nmbs)
	{
		data.pids[data.idx] = fork();
		if(data.pids[data.idx] == 0)
			child(data, envp);
		data.idx++;
	}
	close_pipes(&data);
	convert_fd_to_list(data);
	close(data.fd_bi[0]);
	close(data.fd_bi[1]);
	wait_pids(&data);
	free(data.pids);
	dup2(pipe_stdin, STDIN_FILENO);
	parent_close(&data, "success", 0);
	if (g_cmd_table->status == 42)
		exit_bi(1);
}
