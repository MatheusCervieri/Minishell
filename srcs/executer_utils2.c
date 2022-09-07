/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:30:08 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/07 10:39:12 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_there_quotes(char *parameter)
{
	int	i;

	i = 0;
	while (parameter[i])
	{
		if (parameter[i] == 39)
			return (1);
		if (parameter[i] == 34)
			return (1);
		i++;
	}
	return (0);
}

void	remove_single_quotes(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
	while ((*tokens)[i] != NULL)
	{
		if ((*tokens)[i][ft_strlen((*tokens)[i]) - 1] == '\'')
			(*tokens)[i][ft_strlen((*tokens)[i]) - 1] = '\0';
		if ((*tokens)[i][0] == '\'')
		{
			j = 0;
			while ((*tokens)[i][++j])
			(*tokens)[i][j - 1] = (*tokens)[i][j];
			(*tokens)[i][j - 1] = '\0';
		}
		i++;
	}
}

void	init_data_utils(t_pipex *data)
{
	data->cmd_nmbs = g_cmd_table->n_of_cmds;
	data->pipe_nmbs = 2 * (data->cmd_nmbs - 1);
	data->idx = 0;
	data->success = 0;
	data->path = 1;
	data->here_doc = g_cmd_table->here_doc;
	data->append = g_cmd_table->append;
	data->limiter = g_cmd_table->limiter;
}
