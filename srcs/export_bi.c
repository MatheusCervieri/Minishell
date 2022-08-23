/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:11:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/23 10:00:57 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int find_equal_position(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if(arg[i] == "=")
			return (i);
		i++;
	}
	return (0);	
}

int already_var(t_list *envp, char *arg)
{
	while(envp)
	{
	if (ft_strncmp((char*)envp->content, arg, find_equal_position) == 0)
	{
		return (1);
	}
		envp = envp->next;	
	}
	//fazer um strncmp com cada elemento da lista procurando para ver se tem alguma igual a var;
	// se tiver alguma igual retorna 1 e troca o valor da variavel.
	// se não tiver nenhuma igual retorna zero e dae adiciona na lista.
	return (0);
}

void change_var_value(t_list *envp)
{
}

void change_or_create(t_list *envp, char *arg)
{
		// Pesquisar se já existe.
	if (!(already_var(envp, arg) == 1))
		ft_lstadd_front(&envp, ft_lstnew((char *)arg));
	// NA VERDADE EU VOU TER QUE ADICIONAR CADA COMANDO NESSA MERDA
}

void export_bi(char **cmd_args, t_list *envp)
{
	
}
*/