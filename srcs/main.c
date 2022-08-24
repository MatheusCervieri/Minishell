/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:23:53 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/23 21:36:56 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_struct(void)
{
	int i;
	i = 0;
	printf("**table\n");
	while (g_cmd_table->table[i])
	{
		printf("COMAND TABLE:::");
		printf("%s\n\n", g_cmd_table->table[i]);
		i++;
	}
	printf("\n");
	printf("n_of_cmds\n");
	printf("%i", g_cmd_table->n_of_cmds);
	printf("\n");
	printf("infile\n");
	printf("%s", g_cmd_table->infile);
	printf("\n");
	printf("outfile\n");
	printf("%s", g_cmd_table->outfile);
	printf("\n");
	printf("infile_exists\n");
	printf("%i", g_cmd_table->infile_exists);
	printf("\n");
	printf("outfile_exists\n");
	printf("%i", g_cmd_table->outfile_exists);
	printf("\n");
	printf("here_doc\n");
	printf("%i", g_cmd_table->here_doc);
	printf("\n");
	printf("append\n");
	printf("%i", g_cmd_table->append);
	printf("\n");
	printf("limiter\n");
	printf("%s", g_cmd_table->limiter);
	printf("\n");
	printf("status\n");
	printf("%i", g_cmd_table->status);
	printf("\n");
	printf("last_status\n");
	printf("%i", g_cmd_table->last_status);
	printf("\n");
}


void	make_list(t_list **list, char **envp)
{
	int i;
	t_list *head;
	i = 1;
	
	while(envp[i])
	{
		ft_lstadd_back(list, ft_lstnew((char *)envp[i]));
		//if (i == 0)
			//head = *list;
		i++;
	}
	
	//printf("%s \n", (char *) head->next->content);
}

void	print_list(t_list *list)
{
	while(list)
	{
		printf("%s \n", (char *) list->content);
		list = list->next;
	}
}


int	main(int argc, char **argv, char **envp)
{
	/*
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	print_list(g_cmd_table->envp);
	char **teste = convert_list_to_char(g_cmd_table->envp);
	printf("-------------------------------\n");
	printf("%s \n", teste[4]);
	*/
	
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	print_list(g_cmd_table->envp);
	g_cmd_table->status = 0;
	init_global();
	char **comands_string;
	comands_string = malloc(sizeof(char*) * 3);
	comands_string[0] = ft_strdup("export TESTE=JUJUBA BALEIA=MAÇA ");
	comands_string[1] = ft_strdup("grep a");
	comands_string[2] = ft_strdup("grep d");
	g_cmd_table->table = comands_string;
	g_cmd_table->n_of_cmds = 3;
	g_cmd_table->infile = ft_strdup("text1.txt");
	g_cmd_table->outfile = ft_strdup("text8.txt");
	g_cmd_table->infile_exists = 1;
	g_cmd_table->outfile_exists = 1;
	g_cmd_table->here_doc = 0;
	g_cmd_table->append = 1;
	g_cmd_table->limiter = ft_strdup("teste");
	executor_handler();
	free(g_cmd_table->infile);
	free(g_cmd_table->outfile);
	free(g_cmd_table->limiter);
	free(comands_string[0]);
	free(comands_string[1]);
	free(comands_string[2]);
	free(comands_string);
	
	/*
		g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	char *baleia = ft_strdup("baleiavermelinha");
	printf("%i", lst_find_var_p(g_cmd_table->envp, baleia));
	*/
/*
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	ft_lstadd_back(&(g_cmd_table->envp), ft_lstnew((char *)envp[1]));
	ft_lstadd_back(&(g_cmd_table->envp), ft_lstnew((char *)envp[2]));
	print_list(g_cmd_table->envp);
	char **cmd_args;
	cmd_args = malloc(sizeof(char*) * 4);
	cmd_args[0] = ft_strdup("dsadsada");
	cmd_args[1] = ft_strdup("BALEIAvermelinha12345");
	cmd_args[2] = ft_strdup("DASDSADS");
	cmd_args[3] = NULL;
	unset_bi(cmd_args);
	printf("------------------------------------------------------------------\n");
	print_list(g_cmd_table->envp);
	*/
	/*
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	print_list(g_cmd_table->envp);
	printf("---------------------------------------------------- \n");
	char **cmd_args;
	cmd_args = malloc(sizeof(char*) * 5);
	cmd_args[0] = ft_strdup("export");
	cmd_args[1] = ft_strdup("TESTE=giboia");
	cmd_args[2] = ft_strdup("OLDPWD=BALEIA");
	cmd_args[3] = ft_strdup("ESTRATOSFERA=terrestre");
	cmd_args[4] = ft_strdup("GIBOIA=agressiva");
	cmd_args[5] = NULL;
	export_bi(cmd_args);
	print_list(g_cmd_table->envp);
	char **cmd_args2;
	cmd_args2 = malloc(sizeof(char*) * 3);
	cmd_args2[0] = ft_strdup("unset");
	cmd_args2[1] = ft_strdup("TESTE");
	cmd_args2[2] = NULL;
	remove_node(&(g_cmd_table->envp), lst_find_var_p(g_cmd_table->envp, "TESTE"));
	print_list(g_cmd_table->envp);
	*/
	/*
	char **args;
	args = malloc(sizeof(char*) * 3);
	args[0] = ft_strdup("export");
	args[1] = ft_strdup("TESTE123=ALMONDEGA");
	args[2] = ft_strdup("ZOO=GIRAFA");
	export_bi(args ,g_cmd_table->envp);
	print_list(g_cmd_table->envp);
	*/
}
//printf("%s\n", (char *)list->content);
	//make_list(&list, envp);
	
	//printf("\n\n\n\n");
	//printf("%s \n", (char *) g_cmd_table->envpl->content);
	//print_list();
	
	/*
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	g_cmd_table->status = 0;
	init_global();
	char **comands_string;
	comands_string = malloc(sizeof(char*) * 3);
	comands_string[0] = ft_strdup("grep a");
	comands_string[1] = ft_strdup("grep a");
	comands_string[2] = ft_strdup("grep d");
	g_cmd_table->table = comands_string;
	g_cmd_table->n_of_cmds = 3;
	g_cmd_table->infile = ft_strdup("text1.txt");
	g_cmd_table->outfile = ft_strdup("text8.txt");
	g_cmd_table->infile_exists = 1;
	g_cmd_table->outfile_exists = 1;
	g_cmd_table->here_doc = 0;
	g_cmd_table->append = 1;
	g_cmd_table->limiter = ft_strdup("teste");
	executor_handler(envp);
	free(g_cmd_table->infile);
	free(g_cmd_table->outfile);
	free(g_cmd_table->limiter);
	free(comands_string[0]);
	free(comands_string[1]);
	free(comands_string[2]);
	free(comands_string);
	
	*/
	/*
	int	rtn;
	char *line;
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	g_cmd_table->status = 0;
	line = ft_strdup("echo dadasdsad");
	init_global();
	rtn = 0;
	rtn = parse_line(line);
	//g_cmd_table->infile_exists = 0;
	//g_cmd_table->outfile_exists = 0;
	g_cmd_table->n_of_cmds = g_cmd_table->n_of_cmds - 1;
	
	executor_handler(envp);
	print_struct();
	return (rtn);
	*/
	
