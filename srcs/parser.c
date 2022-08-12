/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:07:41 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/12 01:35:16 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_table	*cmd_table;

t_list	*lexer(char *line)
{
	char	**split_line;
	t_list	*tmp;
	t_list	*rtn;

	split_line = ft_split(line, ' ');
	rtn = ft_lstnew(*split_line);
	split_line++;
	while(*split_line)
	{
		tmp = ft_lstnew(*split_line);
		ft_lstadd_back(&rtn, tmp);
		split_line++;
	}
	return (rtn);
}

int	parse_line(char *line)
{
	t_list *tmp;
	if (!line)
		return (0);
	if (ft_strncmp(line, "exit", 5) == 0)
		return (1);
	tmp = lexer(line);
	//TODO BUILD PARSER
	if (tmp)
		return(2);
	return (0);
}