/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:01:42 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/06 19:47:30 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_bi(int code)
{
	if (code == 2)
	{
		write(1, "exit\n", 6);
		free(g_cmd_table->infile);
		free(g_cmd_table->outfile);
		clear_memory();
		exit(0);
	}
	if (code == 3)
	{
		write(1, "exit\n", 6);
		free_global();
		clear_memory();
		exit(0);
	}
}
