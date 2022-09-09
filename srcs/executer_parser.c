/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:26:30 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/08 22:22:10 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_spaces_quote(char **parameter)
{
	int		i;
	char	q_type;

	i = -1;
	while (parameter[0][++i])
	{
		while (parameter[0][i] && (parameter[0][i] != '"'
				&& parameter[0][i] != '\''))
			i++;
		if (!parameter[0][i])
			return ;
		q_type = parameter[0][i];
		while (parameter[0][++i] != q_type)
			if (parameter[0][i] == ' ')
				parameter[0][i] = 1;
	}
}

void	revert_spaces(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
	while ((*tokens)[i] != NULL)
	{
		j = 0;
		while ((*tokens)[i][j])
		{
			if ((*tokens)[i][j] == 1)
				(*tokens)[i][j] = ' ';
			j++;
		}
		i++;
	}
}

char	**get_parameters(char *parameter)
{
	char	**tokens;
	char	*new_str;

	change_spaces_quote(&parameter);
	new_str = clean_quotes(parameter);
	tokens = ft_split(new_str, ' ');
	free(new_str);
	revert_spaces(&tokens);
	return (tokens);
}
