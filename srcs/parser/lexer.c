/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:54:16 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/21 22:37:23 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lexer(char **split_line)
{
	int		i;
	t_list	*tmp;
	t_list	*rtn;

	i = 0;
	rtn = ft_lstnew(ft_strdup(split_line[i]));
	i++;
	while (split_line[i])
	{
		tmp = ft_lstnew(ft_strdup(split_line[i]));
		ft_lstadd_back(&rtn, tmp);
		i++;
	}
	return (rtn);
}
