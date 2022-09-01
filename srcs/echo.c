/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:00:07 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/01 13:21:40 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_echo(char **cmd_args, int parameter)
{
	int		i;
	char	*print_string;

	i = parameter;
	while (i < args_len(cmd_args))
	{
		if (cmd_args[i][0] == 34 || cmd_args[i][0] == 39)
		{
			if (cmd_args[i][0] == 34)
				print_string = ft_strtrim(cmd_args[i], "\"");
			if (cmd_args[i][0] == 39)
				print_string = ft_strtrim(cmd_args[i], "\'");
			ft_putstr_fd(print_string, 1);
			free(print_string);
		}
		else
			ft_putstr_fd(cmd_args[i], 1);
		if (i != args_len(cmd_args) - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

void	echo_bi(char **cmd_args)
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
}
