/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:01:42 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/07 20:20:40 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_all_digits(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_isdigit(string[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	get_exit_code(void)
{
	char	**tmp;
	int		exit_code;

	tmp = ft_split(g_cmd_table->table[0], ' ');
	if (tmp[1] != NULL)
	{
		if (is_all_digits(tmp[1]) == 1)
			exit_code = ft_atoi(tmp[1]);
		else
		{
			exit_code = 2;
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(tmp[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
	}
	free_split_line(tmp);
	return (exit_code);
}

void	exit_bi(int code)
{
	int		exit_code;

	if (code == 2)
	{
		write(1, "exit\n", 6);
		free(g_cmd_table->infile);
		free(g_cmd_table->outfile);
		clear_memory();
		exit(0);
	}
	if (code == 3)
	{
		exit_code = 0;
		exit_code = get_exit_code();
		write(1, "exit\n", 6);
		free_global();
		clear_memory();
		exit(exit_code);
	}
}
