/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:58:42 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/29 21:45:15 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_home_env(char *envp[])
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("HOME", envp[i], 4) == 0)
			path = ft_strdup(envp[i] + 5);
	i++;
	}
	return (path);
}

void	enter_dir(char *dir)
{
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2); 
		ft_putstr_fd(dir, 2); 
		ft_putstr_fd(": No such file or directory", 2); 
	}
}

void	cd_bi(char **cmd_args, char **envp, int fd[2])
{
	char	*home_path;

	if (args_len(cmd_args) == 1)
	{
		home_path = find_home_env(envp);
		enter_dir(home_path);
	}
	if (args_len(cmd_args) == 2)
		enter_dir(cmd_args[1]);
	if (args_len(cmd_args) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	}
	convert_list_to_fd_fds(fd);
}
