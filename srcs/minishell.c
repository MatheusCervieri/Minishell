/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:11:31 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/22 23:10:15 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_table	*g_cmd_table;

int	init_global(void)
{
	if (!g_cmd_table)
		return (1);
	g_cmd_table->infile = ft_strdup("STDIN_FILENO");
	if (!g_cmd_table->infile)
	{
		free(g_cmd_table);
		return (1);
	}
	g_cmd_table->outfile = ft_strdup("STDOUT_FILENO");
	if (!g_cmd_table->outfile)
	{
		free(g_cmd_table);
		free(g_cmd_table->infile);
		return (1);
	}
	g_cmd_table->here_doc = 0;
	g_cmd_table->n_of_cmds = 0;
	g_cmd_table->n_of_pipes = 0;
	g_cmd_table->append = 0;
	g_cmd_table->last_status = g_cmd_table->status;
	g_cmd_table->status = 0;
	return (0);
}

void	free_global(void)
{
	int	i;

	i = -1;
	while (++i < g_cmd_table->n_of_cmds)
		free(g_cmd_table->table[i]);
	free(g_cmd_table->table);
	free(g_cmd_table->infile);
	free(g_cmd_table->outfile);
}

int	prompt(char **line)
{
	char	*buf;
	char	*trimmed;

	buf = readline("minishell> ");
	if (buf == NULL)
		return (1);
	if (*buf == '\0')
		return (2);
	trimmed = ft_strtrim(buf, " ");
	free(buf);
	if (trimmed == NULL)
		return (1);
	*line = ft_strdup(trimmed);
	free(trimmed);
	if (*line == NULL)
		return (1);
	if (*line && **line)
		add_history(*line);
	return (0);
}

int	minishell(void)
{
	char	*line;
	int		rtn;

	rtn = 0;
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	g_cmd_table->status = 0;
	while (rtn != 1)
	{
		rtn = prompt(&line);
		if (rtn == 1)
			break ;
		if (rtn == 2)
			continue ;
		if (init_global())
			break ;
		rtn = parse_line(line);
		if (ft_strncmp(g_cmd_table->table[0], "exit", 5) == 0)
			rtn = 1;
		free(line);
		free_global();
	}
	if (rtn == 1)
		rtn = 0;
	rl_clear_history();
	free(g_cmd_table);
	return (rtn);
}
