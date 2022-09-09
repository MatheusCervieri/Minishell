/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:30:08 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/08 21:39:51 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_single_quotes(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
	while ((*tokens)[i] != NULL)
	{
		if ((*tokens)[i][ft_strlen((*tokens)[i]) - 1] == '\'')
			(*tokens)[i][ft_strlen((*tokens)[i]) - 1] = '\0';
		if ((*tokens)[i][0] == '\'')
		{
			j = 0;
			while ((*tokens)[i][++j])
			(*tokens)[i][j - 1] = (*tokens)[i][j];
			(*tokens)[i][j - 1] = '\0';
		}
		i++;
	}
}

void	init_data_utils(t_pipex *data)
{
	data->cmd_nmbs = g_cmd_table->n_of_cmds;
	data->pipe_nmbs = 2 * (data->cmd_nmbs - 1);
	data->idx = 0;
	data->success = 0;
	data->path = 1;
	data->here_doc = g_cmd_table->here_doc;
	data->append = g_cmd_table->append;
	data->limiter = g_cmd_table->limiter;
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		len;

	len = ft_strlen(s1);
	str = (char *)ft_memjoin(s1, len, s2, 2);
	str[len + 1] = '\0';
	free(s1);
	return (str);
}

char	*clean_quotes(char *parameter)
{
	int		i;
	char	*tmp;
	char	*new_str;
	char	q_type;

	new_str = strdup("");
	i = -1;
	q_type = '\0';
	while (parameter[++i])
	{
		if ((parameter[i] == '"' || parameter[i] == '\'') && !q_type)
			q_type = parameter[i];
		else if (parameter[i] == q_type)
			q_type = '\0';
		else
		{
			tmp = (char *)ft_calloc(2, sizeof(char));
			tmp[0] = parameter[i];
			new_str = ft_strjoin_free(new_str, tmp);
			free(tmp);
		}
	}
	return (new_str);
}
