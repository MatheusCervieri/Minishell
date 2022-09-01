/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:11:31 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/01 10:59:21 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_table	*g_cmd_table;

int	init_global(char *envp[])
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
	g_cmd_table->append = 0;
	g_cmd_table->last_status = g_cmd_table->status;
	g_cmd_table->status = 0;
	*rtn = 0;
	return (*rtn);
}

int	prompt(char **line)
{
	char	*buf;
	char	*trimmed;

	buf = readline("minishell> ");
	if (buf == NULL)
		exit_bi();
	if (*buf == '\0')
		return (2);
	trimmed = ft_strtrim(buf, " ");
	free(buf);
	if (!trimmed)
		return (1);
	if (*trimmed == '\0')
		return (2);
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

	init_global(envp);
	rtn = 0;
	while (rtn != 1 && rtn != 3)
	{
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
			continue ;
		free(line);
		executor_handler();
		free_global();
	}
	clear_memory();
}
