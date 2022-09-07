/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 19:18:23 by ghosthologr       #+#    #+#             */
/*   Updated: 2022/09/07 15:21:41 by ghenaut-         ###   ########.fr       */
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

int	has_quote(char *split_line)
{
	char	*word;

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

char	*token_with_quotes(char **split_line, int *i, char *line)
{
	char		*rtn;
	char		*tmp;
	int			size;
	char		quote_type;

	quote_type = *split_line[*i];
	size = -1;
	rtn = 0;
	tmp = line;
	g_cmd_table->n_of_quotes += 2;
	while (++size < g_cmd_table->n_of_quotes - 1)
		tmp = ft_strchr(++tmp, quote_type);
	size = 3;
	while (*(++tmp) != quote_type)
		size++;
	rtn = (char *)malloc(sizeof(char) * size--);
	rtn[size--] = '\0';
	rtn[size--] = quote_type;
	while (*(--tmp) != quote_type)
		rtn[size--] = *tmp;
	rtn[size] = *tmp;
	return (rtn);
}

char	**tokenize(char **split_line, int size, char *line)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = (char **)malloc(sizeof(char *) * (size + 1));
	i = -1;
	j = 0;
	while (split_line[++i])
	{
		if (*split_line[i] == '"' || *split_line[i] == '\'')
		{
			tokens[j] = token_with_quotes(split_line, &i, line);
			if (!(split_line[i][ft_strlen(split_line[i]) - 1]
				== tokens[j][0] && ft_strlen(split_line[i]) > 1))
				while (++i && split_line[i][ft_strlen(split_line[i]) - 1]
					!= tokens[j][0])
					continue ;
		}
		else
			tokens[j] = ft_strdup(split_line[i]);
		j++;
	}
	tokens[j] = NULL;
	free_split_line(split_line);
	return (tokens);
}

char	**expander(char *line)
{
	int		size;
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		g_cmd_table->status = -1;
		return (NULL);
	}
	size = 0;
	while (split_line[size])
		size++;
	g_cmd_table->n_of_tokens = size;
	split_line = tokenize(split_line, size, line);
	return (split_line);
}
