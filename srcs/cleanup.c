/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:53:07 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/01 22:45:10 by mvieira-         ###   ########.fr       */
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
