/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:17:17 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/18 20:59:21 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(char *argv, t_pipex *pipex)
{
	int		file;
	char	*buf;
	int		loop;
	char	break_line;

	loop = 1;
	break_line = '\n';
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		msg_error("Error to create here_doc_tmp\n", 9);
	while (loop)
	{
		buf = readline(">");
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
		{
			loop = 0;
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
