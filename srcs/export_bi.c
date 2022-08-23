/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:11:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/23 16:14:10 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_node(t_list **head, int position)
{
	t_list *aux;
	t_list *prev_node;
	t_list *next_node;
	int i;
	aux = *head;
	i = 0;
	while(aux)
	{
		next_node = aux->next;
		if (i == position)
		{
			prev_node->next = next_node;
			free(aux);
			break ;	
		}
		prev_node = aux;
		i++;
		aux = aux->next;
	}
}

void	change_node(t_list **head, int position, char *arg)
{
	t_list *aux;

	int i;
	aux = *head;
	i = 0;
	while(aux)
	{

		if (i == position)
		{
			aux->content = ft_strdup(arg);
			break ;	
		}
		i++;
		aux = aux->next;
	}
}


int find_equal_position(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if(arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);	
}


int already_var(t_list *envp, char *arg)
{
	
	while(envp)
	{
	if (ft_strncmp((char*)envp->content, arg, find_equal_position(arg)) == 0)
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

int	lst_find_var_p(t_list *head, char *var_name)
{
	int p;
	p = 0;
	while (head)
	{
		if (ft_strncmp(head->content, var_name, find_equal_position(var_name) + 1) == 0)
			return (p);
		p++;
		head = head->next;
	}
	return (-1);
}


void change_or_create(char *arg)
{
	if (find_equal_position(arg) > 0)
	{
	if (lst_find_var_p(g_cmd_table->envp, arg) >= 0)
	{
		change_node(&(g_cmd_table->envp), lst_find_var_p(g_cmd_table->envp, arg), arg);
	}
	else 
		ft_lstadd_back(&(g_cmd_table->envp), ft_lstnew((char *)arg));
	}
}

void export_bi(char **cmd_args)
{
	int i;
	if(args_len(cmd_args) == 0)
	{
		printf("export declare");
	}
	else
	{
		i = 0;
		while (i < args_len(cmd_args))
		{
		change_or_create(cmd_args[i]);
		i++;
		}
	}
}

//falta implementar para escrever todas as variáveis de ambiente - só fazer um if se tem igual
//falta implementar o export sem nenhum parametro