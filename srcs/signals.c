/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:59:51 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/12 12:36:02 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc_handler()
{
	ft_putendl_fd("", 1);
	init_shell();
}

void	ctrld_handler()
{
	ft_putendl_fd("", 1);
	init_shell();
}

void	signals()
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
	