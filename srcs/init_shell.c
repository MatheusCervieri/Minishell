/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:11:31 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/12 01:32:36 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		rtn = parse_line(line);
	}
	rl_clear_history();
	free(line);
	return (0);
}