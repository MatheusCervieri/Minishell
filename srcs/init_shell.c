/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:11:31 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/12 12:41:38 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_shell(void)
{
	char	*line;

	while (1)
	{
		signals();
		line = readline("minishell> ");
		if (line && *line)
			add_history(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
	}
	rl_clear_history();
	free(line);
	return (0);
}
