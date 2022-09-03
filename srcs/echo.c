/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:00:07 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/02 21:31:56 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_no_quotes(const char *str, int pos)
{
	char	*print_string;

	if (pos == 1)
	{
		if (str[0] == 34)
			print_string = ft_strtrim(str, "\"");
		if (str[0] == 39)
			print_string = ft_strtrim(str, "\'");
		ft_putstr_fd(print_string, 1);
		free(print_string);
	}
	if (pos == 2)
	{
		if (str[ft_strlen(str) - 1] == 34)
			print_string = ft_strtrim(str, "\"");
		if (str[ft_strlen(str) - 1] == 39)
			print_string = ft_strtrim(str, "\'");
		ft_putstr_fd(print_string, 1);
		free(print_string);
	}
}

void	write_echo(char **cmd_args, int parameter)
{
	int		i;
	int		len;

	i = parameter;
	while (i < args_len(cmd_args))
	{
		len = ft_strlen(cmd_args[i]) - 1;
		if (cmd_args[i][0] == 34 || cmd_args[i][0] == 39)
			print_no_quotes(cmd_args[i], 1);
		else if (cmd_args[i][len] == 34 || cmd_args[i][len] == 39)
			print_no_quotes(cmd_args[i], 2);
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
