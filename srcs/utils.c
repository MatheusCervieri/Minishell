/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:24:34 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/24 18:45:19 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*make_list(char **envp)
{
	int	i;
	t_list *lst;

	i = 0;
	lst = ft_lstnew(envp[i]);
	while (envp[++i])
		ft_lstadd_back(&lst, ft_lstnew(envp[i]));
	return (lst);
}
