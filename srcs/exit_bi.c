/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:01:42 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/01 21:04:37 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_bi(void)
{
	write(1, "exit\n", 6);
}
