/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:18:03 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/01 23:26:14 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lst_find_var_unset(t_list *head, char *var_name)
{
	int		p;
	char	*tmp;

	p = 0;
	while (head)
	{
		tmp = (char *)head->content;
		if (ft_strncmp(tmp, var_name, ft_strlen(var_name)) == 0)
			if (tmp[ft_strlen(var_name)] == '=')
				return (p);
		p++;
		head = head->next;
	}
	return (-1);
}

void	remove_node_loop(t_list	**aux_aux, t_list **prev_node_aux,
		t_list **next_node_aux, int position)
{
	t_list	*aux;
	t_list	*prev_node;
	t_list	*next_node;
	int		i;

	aux = *aux_aux;
	prev_node = *prev_node_aux;
	next_node = *next_node_aux;
	i = 0;
	while (aux)
	{
		next_node = aux->next;
		if (i == position)
		{
			prev_node->next = next_node;
			free(aux->content);
			free(aux);
			break ;
		}
		prev_node = aux;
		i++;
		aux = aux->next;
	}
}

void	remove_node(t_list **head, int position)
{
	t_list	*aux;
	t_list	*prev_node;
	t_list	*next_node;

	if (position >= 0)
	{
		aux = *head;
		if (position == 0)
			*head = (*head)->next;
		else
		{
			remove_node_loop(&aux, &prev_node, &next_node, position);
		}
	}
}

void	unset_bi(char **cmd_args)
{
	int	i;

	if (args_len(cmd_args) > 0)
	{
		i = 1;
		while (i < args_len(cmd_args))
		{
			remove_node(&(g_cmd_table->envp),
				lst_find_var_unset(g_cmd_table->envp, cmd_args[i]));
			i++;
		}
	}
}
