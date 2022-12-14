/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:11:31 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/08 22:26:38 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_table	*g_cmd_table;

int	init_global(char *envp[], int *rtn)
{
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!g_cmd_table)
	{
		printf("malloc error");
		exit(1);
	}
	g_cmd_table->envp = make_list(envp);
	if (!g_cmd_table->envp)
	{
		printf("malloc error");
		free(g_cmd_table);
		exit(1);
	}
	g_cmd_table->status = 0;
	g_cmd_table->last_status = g_cmd_table->status;
	g_cmd_table->signal = 0;
	*rtn = 0;
	return (0);
}

int	reset_global(int *rtn)
{
	g_cmd_table->infile = ft_strdup("STDIN_FILENO");
	if (!g_cmd_table->infile)
	{
		free(g_cmd_table);
		*rtn = 3;
		return (*rtn);
	}
	g_cmd_table->outfile = ft_strdup("STDOUT_FILENO");
	if (!g_cmd_table->outfile)
	{
		free(g_cmd_table);
		free(g_cmd_table->infile);
		*rtn = 3;
		return (*rtn);
	}
	g_cmd_table->here_doc = 0;
	g_cmd_table->n_of_cmds = 0;
	g_cmd_table->n_of_pipes = 0;
	g_cmd_table->n_of_quotes = 0;
	g_cmd_table->n_of_d_quotes = 0;
	g_cmd_table->n_of_tokens = 0;
	g_cmd_table->append = 0;
	g_cmd_table->last_status = g_cmd_table->status;
	g_cmd_table->status = 0;
	return (*rtn);
}

int	prompt(char **line)
{
	char	*buf;
	char	*trimmed;

	buf = readline("\033[01;34mminishell\033[32m ???\033[00m ");
	if (buf == NULL)
		exit_bi(2);
	if (*buf == '\0')
		return (2);
	trimmed = ft_strtrim(buf, " ");
	free(buf);
	if (!trimmed)
		return (1);
	if (*trimmed == '\0')
	{
		free(trimmed);
		return (2);
	}
	*line = ft_strdup(trimmed);
	free(trimmed);
	if (*line == NULL)
		return (1);
	if (*line && **line)
		add_history(*line);
	return (0);
}

void	minishell(char *envp[])
{
	char	*line;
	int		rtn;

	init_global(envp, &rtn);
	while (rtn != 1 && rtn != 3)
	{
		rtn = 0;
		signal(SIGINT, ctrlc_handler);
		signal(SIGQUIT, SIG_IGN);
		if (g_cmd_table->signal == 1)
			break ;
		if (reset_global(&rtn))
			break ;
		rtn = prompt(&line);
		if (rtn == 2)
			continue ;
		if (parse_line(line))
			rtn = 4;
		free(line);
		if (rtn != 4)
			executor_handler();
		free_global();
	}
	clear_memory();
}
