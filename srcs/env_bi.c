/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 08:59:18 by mvieira-          #+#    #+#             */
/*   Updated: 2022/09/07 11:14:34 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	args_len(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		i++;
	}
	return (i);
}

void	env_bi(char **cmd_args)
{
	char	**envp;
	int		i;

	envp = convert_list_to_char();
	if (args_len(cmd_args) > 1)
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(cmd_args[1], 2);
		ft_putstr_fd("’: No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		g_cmd_table->status = 1;
	}
	else
		print_envp(envp);
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}	
	free(envp);
}
