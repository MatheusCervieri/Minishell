/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 19:18:23 by ghosthologr       #+#    #+#             */
/*   Updated: 2022/08/19 21:50:29 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_split_line(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
}

char	*join_with_space(char *str1, char *str2)
{
	char *tmp;

	tmp = ft_strjoin(str1, " ");
	free(str1);
	str1 = ft_strjoin(tmp, str2);
	return (str1);
}

int	has_quote(char *split_line)
{
	char *word;

	word = split_line;
	while ((*word != '"' && ft_strncmp(word, "'", 1)) && *word)
	{
		word++;
	}
	if (*word == '"' || !ft_strncmp(word, "'", 1))
	{
		return (1);
	}
	return (0);
}

char	**expander(char **split_line)
{
	char	**new_line;
	int		i;
	int		j;

	j = 0;
	while (split_line[j])
		j++;
	new_line = (char **)malloc(sizeof(split_line) * (j +  1));
	i = -1;
	j = 0;
	while (split_line[++i])
	{
		if (*split_line[i] == '"' || !ft_strncmp(split_line[i], "'", 1))
		{
			new_line[j] = ft_strdup(split_line[i]);
			while (split_line[++i])
			{
				new_line[j] = join_with_space(new_line[j], split_line[i]);
				if (has_quote(split_line[i]))
					break ;
			}
		}
		else
			new_line[j] = ft_strdup(split_line[i]);
		j++;
	}
	new_line[j] = NULL;
	free_split_line(split_line);
	return(new_line);
}
