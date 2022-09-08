/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:09:52 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/08 10:20:20 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*my_getenv(char *token)
{
	t_list	*tmp;

	if (!strlen(token))
		return (NULL);
	tmp = g_cmd_table->envp;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, token, strlen(token)) == 0)
			return (ft_strdup(&(((char *)tmp->content)[strlen(token) + 1])));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*sanitize_token(const char *token)
{
	int		i;
	char	*rtn;

	rtn = (char *)malloc(strlen(token) + 1);
	i = 0;
	rtn[i] = token[i];
	i++;
	while (ft_isalpha(token[i]) || ft_isdigit(token[i]) || token[i] == '?')
	{
		rtn[i] = token[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	*expand(char *line)
{
	int		len;
	char	*token;
	char	*rtn;

	len = ft_strlen(line);
	token = ft_strchr(line, '$');
	token = sanitize_token(token);
	if (token[1] == '?' && token[2] == '\0')
	{
		free(token);
		return (ft_itoa(g_cmd_table->last_status));
	}
	rtn = my_getenv(&token[1]);
	free(token);
	if (rtn)
	{
		token = ft_strdup(rtn);
		free(rtn);
		return (token);
	}
	if (len == 1)
		return (ft_strdup(line));
	else
		return (ft_strdup(""));
}

void	expand_line(char **line)
{
	int		j;
	int		k;
	char	*expanded_line;
	char	*rtn;

	j = -1;
	expanded_line = (char *)ft_calloc(10240, sizeof(char));
	while (line[0][++j] != '$')
		expanded_line[j] = line[0][j];
	rtn = expand(&(line[0][j]));
	k = -1;
	while (rtn[++k])
		expanded_line[j + k] = rtn[k];
	k = j + k;
	while (line[0][j] != ' ' && line[0][j] != '\"'
		&& line[0][j] != '\0' && line[0][j] != '\'')
		j++;
	if (line[0][j])
		while (line[0][j])
			expanded_line[k++] = line[0][j++];
	expanded_line[k] = '\0';
	free(rtn);
	free(*line);
	*line = ft_strdup(expanded_line);
	free(expanded_line);
}

void	*expand_env(void *content)
{
	char	*tmp;

	tmp = ft_strdup((char *)content);
	if (tmp[0] == '\'')
		return (tmp);
	else
		while (ft_strchr(tmp, '$'))
			expand_line(&tmp);
	return (tmp);
}
