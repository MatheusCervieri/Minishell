/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:53:07 by ghenaut-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/25 17:24:21 by ghenaut-         ###   ########.fr       */
=======
/*   Updated: 2022/08/25 20:10:34 by ghenaut-         ###   ########.fr       */
>>>>>>> a09e60a317bb093cb2d7f91ab92c50b8146de697
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_line(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
}

int	print_and_return(const char *msg, int err_code)
{
	printf("%s\n", msg);
	return (err_code);
}

void	clear_memory(void)
{
	rl_clear_history();
	ft_lstclear(&g_cmd_table->envp, free);
	free(g_cmd_table);
}


void	free_global(void)
{
	int	i;

	i = -1;
	while (++i < g_cmd_table->n_of_cmds)
		free(g_cmd_table->table[i]);
	free(g_cmd_table->table);
	free(g_cmd_table->infile);
	free(g_cmd_table->outfile);
}
