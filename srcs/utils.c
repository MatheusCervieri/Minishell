/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:51:22 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/25 18:15:37 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_struct(void)
{
	int	i;

	i = 0;
	printf("**table\n");
	while (g_cmd_table->table[i])
	{
		printf("COMAND TABLE:::");
		printf("%s\n\n", g_cmd_table->table[i]);
		i++;
	}
	printf("\n");
	printf("n_of_cmds\n");
	printf("%i", g_cmd_table->n_of_cmds);
	printf("\n");
	printf("infile\n");
	printf("%s", g_cmd_table->infile);
	printf("\n");
	printf("outfile\n");
	printf("%s", g_cmd_table->outfile);
	printf("\n");
	printf("infile_exists\n");
	printf("%i", g_cmd_table->infile_exists);
	printf("\n");
	printf("outfile_exists\n");
	printf("%i", g_cmd_table->outfile_exists);
	printf("\n");
	printf("here_doc\n");
	printf("%i", g_cmd_table->here_doc);
	printf("\n");
	printf("append\n");
	printf("%i", g_cmd_table->append);
	printf("\n");
	printf("limiter\n");
	printf("%s", g_cmd_table->limiter);
	printf("\n");
	printf("status\n");
	printf("%i", g_cmd_table->status);
	printf("\n");
	printf("last_status\n");
	printf("%i", g_cmd_table->last_status);
	printf("\n");
}

void	make_list(t_list **list, char **envp)
{
	int	i;

	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(list, ft_lstnew((char *)envp[i]));
		i++;
	}
}

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s \n", (char *) list->content);
		list = list->next;
	}
}
