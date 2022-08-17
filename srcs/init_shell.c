/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:11:31 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/17 11:39:27 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_shell(char **envp)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line && *line)
			add_history(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			break;
		if (ft_strncmp(line, "program", 8) == 0)
			executor_handler(envp);
	}
	rl_clear_history();
	free(line);
	return (0);
}
