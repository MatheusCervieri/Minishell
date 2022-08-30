/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:02:21 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/30 16:20:49 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export_no_parameters(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	lst_find_var_p(t_list *head, char *var_name)
{
	int	p;

	p = 0;
	while (head)
	{
		if (ft_strncmp((char *)head->content, var_name,
				find_equal_position(var_name) + 1) == 0)
			return (p);
		p++;
		head = head->next;
	}
	return (-1);
}
