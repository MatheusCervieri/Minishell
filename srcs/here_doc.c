/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:17:17 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/01 13:02:23 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_loop(char *limiter)
{
	char	*buf;

	while (g_cmd_table->here_doc_loop)
	{
		if (g_cmd_table->here_doc_loop != 0)
			buf = readline(">");
		if (!ft_strncmp(limiter, buf, ft_strlen(limiter)))
		{
			g_cmd_table->here_doc_loop = 0;
			free(buf);
		}
		else
		{
			write(g_cmd_table->here_doc_file, buf, ft_strlen(buf));
			ft_putstr_fd("\n", g_cmd_table->here_doc_file);
			free(buf);
		}
	}
}

void	here_doc(char *limiter, t_pipex *pipex)
{
	char	*buf;
	int		loop;
	char	break_line;

	signal(SIGINT, ctrlc_here_doc_handler);
	g_cmd_table->here_doc_loop = 1;
	g_cmd_table->here_doc_file = open(".heredoc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	here_doc_loop(limiter);
	close(g_cmd_table->here_doc_file);
	exit(0);
}
