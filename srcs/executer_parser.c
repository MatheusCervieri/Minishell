/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:26:30 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/08 21:41:48 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_double_quotes(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
	while ((*tokens)[i] != NULL)
	{
		if ((*tokens)[i][ft_strlen((*tokens)[i]) - 1] == '\"')
			(*tokens)[i][ft_strlen((*tokens)[i]) - 1] = '\0';
		if ((*tokens)[i][0] == '\"')
		{
			j = 0;
			while ((*tokens)[i][++j])
			(*tokens)[i][j - 1] = (*tokens)[i][j];
			(*tokens)[i][j - 1] = '\0';
		}
		i++;
	}
}

void	change_spaces_quote(char **parameter)
{
	int		i;
	char	q_type;

	i = -1;
	while (parameter[0][++i] && (parameter[0][i] != '"' && parameter[0][i] != '\''))
		continue;
	if (!parameter[0][i])
		return ;
	q_type = parameter[0][i];
	while (parameter[0][++i] != q_type)
		if (parameter[0][i] == ' ')
			parameter[0][i] = 1;
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
