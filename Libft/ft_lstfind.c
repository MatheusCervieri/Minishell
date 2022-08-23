/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:20:43 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/23 12:09:13 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *head, void *target)
{
	while (head)
	{
		if (head->content == target)
			return (head);
		head = head->next;
	}
	return (NULL);
}
