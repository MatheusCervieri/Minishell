/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:17:17 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/05 19:23:38 by ghenaut-         ###   ########.fr       */
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
		if (buf == NULL)
		{
			printf("%s (wanted `%s')", HD_ERROR, limiter);
			break ;
		}
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

void	here_doc(char *limiter, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
	signal(SIGINT, ctrlc_here_doc_handler);
	g_cmd_table->here_doc_loop = 1;
	g_cmd_table->here_doc_file = open(".heredoc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	here_doc_loop(limiter);
	close(g_cmd_table->here_doc_file);
	free_global();
	clear_memory();
	exit(0);
}

void	handle_heredoc(t_pipex *data, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		here_doc(data->limiter, envp);
	waitpid(pid, NULL, 0);
	data->infile = open(".heredoc_tmp", O_RDONLY);
	if (data->infile < 0)
		msg_error("Can`t open here_doc file\n", 7);
}
