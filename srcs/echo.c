/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:00:07 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/29 21:45:11 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_echo(char **cmd_args, int parameter)
{
	int	i;

	i = parameter;
	while (i < args_len(cmd_args))
	{
		ft_putstr_fd(cmd_args[i], 1);
		if (i != args_len(cmd_args) - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

void	echo_bi(char **cmd_args, int fd[2])
{
	if (args_len(cmd_args) == 1)
	{
		ft_putstr_fd("\n", 1);
	}
	else
	{
		if (ft_strncmp(cmd_args[1], "-n", 3) == 0)
			write_echo(cmd_args, 2);
		else
		{
			write_echo(cmd_args, 1);
			ft_putstr_fd("\n", 1);
		}
	}
	convert_list_to_fd_fds(fd);
}