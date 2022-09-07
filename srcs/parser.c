/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:07:41 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/07 15:22:11 by ghenaut-         ###   ########.fr       */
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
	int	found_quote;

	i = -1;
	found_quote = 0;
	while (line[++i])
	{
		if ((line[i] == '"' || line[i] == '\'') && !found_quote)
			found_quote = 1;
		else if ((line[i] == '"' || line[i] == '\'') && found_quote)
			found_quote = 0;
		if ((line[i] == ';' || line[i] == '\\' || line[i] == '&')
			&& !found_quote)
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
	char	**split_line;

	if (!line)
		return (0);
	g_cmd_table->status = check_line(line);
	if (g_cmd_table->status != 0)
		return (1);
	split_line = expander(line);
	if (g_cmd_table->status == -1)
		return (print_and_return("malloc error", 1));
	if (g_cmd_table->n_of_tokens < 2 && is_special(split_line[0]))
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putstr_fd(split_line[0], 2);
		ft_putstr_fd("'\n", 2);
		free_split_line(split_line);
		return (1);
	}
	tmp_cmd_table = lexer(split_line);
	free_split_line(split_line);
	parser(tmp_cmd_table);
	ft_lstclear(&tmp_cmd_table, free);
	return (0);
}
