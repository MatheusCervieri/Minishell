/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:11:31 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/20 00:54:53 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_table	*cmd_table;

void	init_global(void)
{
	cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	cmd_table->infile = ft_strdup("STDIN_FILENO");
	cmd_table->outfile = ft_strdup("STDOUT_FILENO");
	cmd_table->here_doc = 0;
	cmd_table->n_of_cmds = 0;
	cmd_table->n_of_pipes = 0;
	cmd_table->append = 0;
}

int	init_shell(void)
{
	char	*line;
	int		rtn;

	rtn = 0;
	while (rtn == 0)
	{
		line = readline("minishell> ");
		if (line && *line)
			add_history(line);
		init_global();
		rtn = parse_line(line);
	}
	rl_clear_history();
	free(line);
	return (0);
}
