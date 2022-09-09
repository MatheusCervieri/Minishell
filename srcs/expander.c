/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 19:18:23 by ghosthologr       #+#    #+#             */
/*   Updated: 2022/09/08 22:22:32 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_with_space(char *str1, char *str2)
{
	char	*tmp;

	tmp = ft_strjoin(str1, " ");
	free(str1);
	str1 = ft_strjoin(tmp, str2);
	free(tmp);
	return (str1);
}

static void	change_spaces_quote(char **parameter)
{
	int		i;
	char	q_type;

	i = -1;
	while (parameter[0][++i] != '\0')
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

static void	revert_spaces(char ***tokens)
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

char	**expander(char *line)
{
	char	**tokens;

	change_spaces_quote(&line);
	tokens = ft_split(line, ' ');
	revert_spaces(&tokens);
	return (tokens);
}
