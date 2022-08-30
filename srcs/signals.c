/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:25:16 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/30 11:24:07 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc_handler()
{
	g_cmd_table.status = 130;
    ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrlc_child_handler()
{
	g_cmd_table.status = 130;
    ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	ctrlc_here_doc_handler()
{
	g_cmd_table.status = 130;
    ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	ctrld_handler()
{
	exit_bi();
}

void	signals_parent(void)
{
	/*
	struct sigaction sa;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &ctrlc_handler;
	sigaction(SIGINT, &sa, NULL);
	*/
	signal(SIGINT, ctrlc_handler);	
	//signal(SIGQUIT, ctrld_handler);	
}

void	signals_child(void)
{
	/*
	struct sigaction sa;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &ctrlc_handler;
	sigaction(SIGINT, &sa, NULL);
	*/
	signal(SIGINT, ctrlc_child_handler);	
	signal(SIGQUIT, ctrld_handler);	
}