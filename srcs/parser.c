/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:07:41 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/22 20:15:51 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(const char *line)
{
	int	d_quotes;
	int	quotes;

	d_quotes = 0;
	quotes = 0;
	while (*line)
	{
		if (*line == '"')
			d_quotes++;
		else if (*line == '\'')
			quotes++;
		line++;
	}
	if (d_quotes % 2 != 0 || quotes % 2 != 0)
		return (1);
	return (0);
}

int	check_prohibited(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ';' || line[i] == '\\' || line[i] == '&')
			return (1);
	}
	return (0);
}

int	check_line(char *line)
{
	if (check_quotes(line))
		return (print_and_return("Unbalanced quotes", 2));
	if (check_prohibited(line))
		return (print_and_return("invalid operators", 3));
	return (0);
}

int	parser(t_list *tmp_cmd_table)
{
	t_list	*ptr;

	ptr = tmp_cmd_table;
	while (ptr)
	{
		if (is_special((char *)ptr->content))
		{
			handle_special((char *)ptr->content, &ptr);
			if (*((char *)ptr->content) != '|')
				ptr = ptr->next;
		}
		else
		{
			g_cmd_table->n_of_cmds++;
			while (ptr->next && !is_special((char *)ptr->next->content))
				ptr = ptr->next;
		}
		ptr = ptr->next;
	}
	get_cmds(tmp_cmd_table);
	expand_env();
	return (0);
}

int	parse_line(char *line)
{
	t_list	*tmp_cmd_table;
	int		rtn;
	char	**split_line;

	if (!line)
		return (0);
	rtn = check_line(line);
	if (rtn)
		return (rtn);
	split_line = expander(line);
	if (g_cmd_table->status == -1)
		print_and_return("malloc error", 1);
	tmp_cmd_table = lexer(split_line);
	free_split_line(split_line);
	parser(tmp_cmd_table);
	ft_lstclear(&tmp_cmd_table, free);
	return (0);
}