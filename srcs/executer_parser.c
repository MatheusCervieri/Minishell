/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:26:30 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/07 10:27:51 by mvieira-         ###   ########.fr       */
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

void	change_spaces_double_quote(char **parameter)
{
	char	*position;

	position = *parameter;
	while (*(*parameter) != '\0')
	{
		if (*(*parameter) == 34)
		{
			*parameter = *parameter + 1;
			while (*(*parameter) != 34 && *(*parameter) != '\0')
			{
				if (*(*parameter) == ' ')
					*(*parameter) = 1;
				*parameter = *parameter + 1;
			}
		}
		*parameter = *parameter + 1;
	}
	*parameter = position;
}

void	change_spaces_single_quote(char **parameter)
{
	char	*position;

	position = *parameter;
	while (*(*parameter) != '\0')
	{
		if (*(*parameter) == 39)
		{
			*parameter = *parameter + 1;
			while (*(*parameter) != 39 && *(*parameter) != '\0')
			{
				if (*(*parameter) == ' ')
					*(*parameter) = 1;
				*parameter = *parameter + 1;
			}
		}
		*parameter = *parameter + 1;
	}
	*parameter = position;
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

	change_spaces_double_quote(&parameter);
	change_spaces_single_quote(&parameter);
	tokens = ft_split(parameter, ' ');
	revert_spaces(&tokens);
	remove_double_quotes(&tokens);
	remove_single_quotes(&tokens);
	return (tokens);
}
