/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:25:16 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/31 13:00:25 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc_handler(int sing)
{
	g_cmd_table->status = 130;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrlc_child_handler(int sing)
{
	g_cmd_table->status = 130;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	ctrlc_here_doc_handler(int sing)
{
	ft_putstr_fd("Here doc handler", 2);
	g_cmd_table->status = 130;
	g_cmd_table->here_doc_loop = 0;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	close(g_cmd_table->here_doc_file);
}
