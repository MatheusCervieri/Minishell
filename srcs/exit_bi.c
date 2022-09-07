/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:01:42 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/07 16:18:59 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_bi(int code)
{
	int		exit_code;
	char	**tmp;

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
		exit_code = 0;
		tmp = ft_split(g_cmd_table->table[0], ' ');
		if (tmp[1] != NULL)
			exit_code = ft_atoi(tmp[1]);
		free_split_line(tmp);
		write(1, "exit\n", 6);
		free_global();
		clear_memory();
		exit(exit_code);
	}
}
