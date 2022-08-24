/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:16:38 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/23 23:07:55 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "env", 4) == 0)
		return(1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

char	**convert_list_to_char(t_list *ticaratica)
{
	int		size;
	char	**envp;
	int		i;
	t_list *head;
	
	size = ft_lstsize(head);
	head = g_cmd_table->envp;
	envp = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (head)
	{
		envp[i] = ft_strdup((char *)head->content);
		i++;
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}

void execute_builtin(char *cmd, char **cmd_args, char **envp)
{

	if (ft_strncmp(cmd, "env", 4) == 0)
		env_bi(cmd_args, envp);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		cd_bi(cmd_args, envp);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		echo_bi(cmd_args);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		pwd_bi();
	if (ft_strncmp(cmd, "exit", 5) == 0)
		exit_bi(cmd_args);
	if (ft_strncmp(cmd, "export", 7) == 0)
		export_bi(cmd_args);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		unset_bi(cmd_args);
}
