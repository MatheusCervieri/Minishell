/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:25:16 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/29 13:28:14 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc_handler()
{
    ft_putendl_fd("Start to handle signals kaka", 1);
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