/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:25:16 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/30 10:05:57 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc_handler()
{
    exit_bi();
}

void	ctrld_handler()
{
	ft_putendl_fd("", 1);
}

void	signals(void)
{
	/*
	struct sigaction sa;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler;
	sigaction(SIGINT, &sa, NULL);
	*/
	signal(SIGINT, ctrlc_handler);	
	signal(SIGQUIT, ctrld_handler);	
}