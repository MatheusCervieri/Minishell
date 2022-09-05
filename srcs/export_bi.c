/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:11:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/05 01:34:55 by Ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_node(t_list **head, int position, char *arg)
{
	t_list	*aux;
	int		i;

	aux = *head;
	i = 0;
	while (aux)
	{
		if (i == position)
		{
			aux->content = ft_strdup(arg);
			break ;
		}
		i++;
		aux = aux->next;
	}
}

int	find_equal_position(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	already_var(t_list *envp, char *arg)
{
	while (envp)
	{
		if (ft_strncmp((char *)envp->content,
				arg, find_equal_position(arg)) == 0)
		{
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

void	change_or_create(char *arg)
{
	if (find_equal_position(arg) > 0)
	{
		if (lst_find_var_p(g_cmd_table->envp, arg) >= 0)
			change_node(&(g_cmd_table->envp),
				lst_find_var_p(g_cmd_table->envp, arg), arg);
		else
			ft_lstadd_back(&(g_cmd_table->envp),
				ft_lstnew(ft_strdup((char *)arg)));
	}
}

void	export_bi(char **cmd_args)
{
	int		i;
	char	**envp;

	if (args_len(cmd_args) == 1)
	{
		envp = convert_list_to_char();
		print_export_no_parameters(envp);
		i = -1;
		while (envp[++i])
			free(envp[i]);
		free(envp);
	}
	else
	{
		i = 0;
		while (i < args_len(cmd_args))
		{
			change_or_create(cmd_args[i]);
			i++;
		}
	}
}
