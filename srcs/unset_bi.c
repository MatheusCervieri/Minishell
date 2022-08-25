/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:18:03 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/24 21:33:08 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_node(t_list **head, int position)
{
    if (position >= 0)
    {
	t_list *aux;
	t_list *prev_node;
	t_list *next_node;
	int i;
	aux = *head;
	i = 0;
    if(position == 0)
        *head = (*head)->next;
    else
    {
	while(aux)
	{
		next_node = aux->next;
		if (i == position)
		{
			prev_node->next = next_node;
			free(aux);
			break ;	
		}
		prev_node = aux;
		i++;
		aux = aux->next;
	}
    }
    }
}

void unset_bi(char **cmd_args)
{
    if (args_len(cmd_args) > 0)
    {
        int i;

        i = 1;
        while (i < args_len(cmd_args))
        {
            remove_node(&(g_cmd_table->envp), lst_find_var_p(g_cmd_table->envp, cmd_args[i]));
            printf("---------------------------------------------------\n");
            print_list(g_cmd_table->envp);
             printf("---------------------------------------------------\n");
            i++;
        }
    }
}