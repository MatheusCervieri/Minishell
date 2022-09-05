/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:30:08 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/05 18:56:26 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
