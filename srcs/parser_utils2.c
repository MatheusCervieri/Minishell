/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:31:17 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/07 17:02:52 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_error(char *error)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("'\n", 2);
}

int	check_tokens(char **split_line)
{
	int		i;
	char	*error;

	error = NULL;
	if (is_special(*split_line) && split_line[1] == NULL)
		error = ft_strdup(*split_line);
	else if (is_special(*split_line) && is_special(split_line[1]))
		error = ft_strdup(*split_line);
	else
	{
		i = -1;
		while (split_line[++i] && split_line[i][0] != '>')
			continue ;
		if (split_line[i] != NULL)
			if (split_line[i][0] == '>' && split_line[++i] == NULL)
				error = ft_strdup(split_line[i - 1]);
	}
	if (error)
	{
		print_error(error);
		free(error);
		return (1);
	}
	return (0);
}

char	*get_position(char quote_type, char *line)
{
	int		i;
	char	*rtn;

	i = -1;
	rtn = line;
	if (quote_type == '\'')
	{
		g_cmd_table->n_of_quotes += 2;
		while (++i < g_cmd_table->n_of_quotes - 1)
			rtn = ft_strchr(++rtn, quote_type);
	}
	else
	{
		g_cmd_table->n_of_d_quotes += 2;
		while (++i < g_cmd_table->n_of_d_quotes - 1)
			rtn = ft_strchr(++rtn, quote_type);
	}
	return (rtn);
}
