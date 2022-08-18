/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:30:08 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/18 17:29:51 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	init_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_nmbs - 1)
	{
		if (pipe(data->pipe + (2 * i)) < 0)
			parent_close(data, "Failed to pipe\n", 4);
		i++;
	}
}
