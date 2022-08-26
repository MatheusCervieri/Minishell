/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:01:42 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/25 22:17:13 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_bi(int pid)
{
	if (pid != 1)
		exit(42);
	else
	{
		write(1, "exit\n", 6);
		free_global();
		clear_memory();
		exit(0);
	}
}
