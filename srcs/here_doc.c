/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:17:17 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/30 12:48:09 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	here_doc(char *argv, t_pipex *pipex)
{
	//signals_here_doc();
	int		file;
	char	*buf;
	int		loop;
	char	break_line;

	g_cmd_table->here_doc_loop = 1;
	break_line = '\n';
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	g_cmd_table->here_doc_file = file;
	if (file < 0)
		msg_error("Error to create here_doc_tmp\n", 9);
	while (g_cmd_table->here_doc_loop)
	{
		if(g_cmd_table->here_doc_loop != 0)
			buf = readline(">");
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
		{
			g_cmd_table->here_doc_loop = 0;
			free(buf);
		}
		else
		{
			write(file, buf, ft_strlen(buf));
			write(file, &break_line, 1);
			free(buf);
		}
	}
	close(file);
	pipex->infile = file;
	pipex->infile = open(".heredoc_tmp", O_RDONLY);
	if (pipex->infile < 0)
		msg_error("Invalid infile\n", 7);
}
