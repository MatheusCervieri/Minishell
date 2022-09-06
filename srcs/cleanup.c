/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:53:07 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/06 19:50:32 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_line(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
}

int	print_and_return(const char *msg, int err_code)
{
	printf("%s\n", msg);
	return (err_code);
}

void	clear_memory(void)
{
	rl_clear_history();
	ft_lstclear(&g_cmd_table->envp, free);
	free(g_cmd_table);
}

void	free_global(void)
{
	int	i;

	i = -1;
	while (++i < g_cmd_table->n_of_cmds)
		free(g_cmd_table->table[i]);
	if (g_cmd_table->n_of_cmds)
		free(g_cmd_table->table);
	if (g_cmd_table->here_doc)
		free(g_cmd_table->limiter);
	free(g_cmd_table->infile);
	free(g_cmd_table->outfile);
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
