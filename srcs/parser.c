/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:07:41 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/20 00:35:27 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(t_list *tmp_cmd_table)
{
	t_list	*ptr;

	ptr = tmp_cmd_table;
	while(ptr)
	{
		if (is_special((char *)ptr->content))
			handle_special((char *)ptr->content, &ptr);
		else
		{
			cmd_table->n_of_cmds++;
			while (ptr->next && is_special((char *)ptr->content))
				ptr = ptr->next;
		}
		ptr = ptr->next;
	}
	get_cmds(tmp_cmd_table);
	return (0);
}

int	parse_line(char *line)
{
	t_list	*tmp_cmd_table;

	if (!line)
		return (0);
	if (ft_strncmp(line, "exit", 5) == 0)
		return (1);
	tmp_cmd_table = lexer(line);
	parser(tmp_cmd_table);
	return (0);
}