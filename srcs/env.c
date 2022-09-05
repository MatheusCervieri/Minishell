/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:09:52 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/05 19:22:17 by ghenaut-         ###   ########.fr       */
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

char	*expand(char *line, int i)
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
	expanded_line = (char *)ft_calloc(10240, sizeof(char));
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
	char	*tmp;

	i = -1;
	while (g_cmd_table->table[++i])
	{
		tmp = g_cmd_table->table[i];
		if (ft_strchr(tmp, '\''))
		{
			tmp = ft_strchr(tmp, '\'');
			if (tmp[-1] == ' ')
				continue ;
		}
		while (ft_strchr(g_cmd_table->table[i], '$')
			&& g_cmd_table->table[i][0] != '\'')
			expand_line(i);
	}
}
