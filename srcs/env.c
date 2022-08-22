/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:09:52 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/21 22:48:20 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_status(char *token)
{
	if (token[1] == '?' && token[2] == '\0')
		return (ft_itoa(g_cmd_table->last_status));
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

char	*expand(char *line, int i)
{
	int		len;
	char	*token;
	char	*rtn;

	len = ft_strlen(line);
	token = ft_strchr(line, '$');
	token = sanitize_token(token);
	rtn = handle_status(token);
	if (rtn)
		return (rtn);
	rtn = getenv(&token[1]);
	free(token);
	if (rtn)
		return (ft_strdup(rtn));
	else if (len == 1)
		return (g_cmd_table->table[i]);
	else
		return (ft_strdup(""));
}

void	expand_line(int i)
{
	int		j;
	int		k;
	char	*expanded_line;
	char	*rtn;

	j = -1;
	expanded_line = (char *)ft_calloc(1024, sizeof(char));
	while (g_cmd_table->table[i][++j] != '$')
		expanded_line[j] = g_cmd_table->table[i][j];
	rtn = expand(&(g_cmd_table->table[i][j]), i);
	k = -1;
	while (rtn[++k])
		expanded_line[j + k] = rtn[k];
	k = j + k;
	while (g_cmd_table->table[i][j] != ' ' && g_cmd_table->table[i][j] != '\"'
		&& g_cmd_table->table[i][j] != '\0' && g_cmd_table->table[i][j] != '\'')
		j++;
	if (g_cmd_table->table[i][j])
		while (g_cmd_table->table[i][j])
			expanded_line[k++] = g_cmd_table->table[i][j++];
	expanded_line[k] = '\0';
	free(rtn);
	free(g_cmd_table->table[i]);
	g_cmd_table->table[i] = ft_strdup(expanded_line);
	free(expanded_line);
}

void	expand_env(void)
{
	int		i;

	i = -1;
	while (g_cmd_table->table[++i])
		if (ft_strchr(g_cmd_table->table[i], '$') &&
			g_cmd_table->table[i][0] != '\'')
			expand_line(i);
}
