/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:23:53 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/22 17:14:58 by mvieira-         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
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

	
	
	int	rtn;
	char *line;
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	g_cmd_table->status = 0;
	
	
	line = ft_strdup("< text1.txt grep a | grep a | grep d > text2.txt");
	init_global();
	rtn = 0;
	rtn = parse_line(line);
	g_cmd_table->infile_exists = 1;
	g_cmd_table->outfile_exists = 1;
	g_cmd_table->infile = ft_strdup("text1.txt");
	printf("OUTFILE: %s\n", g_cmd_table->outfile);
	int i;
	i = 0;
	g_cmd_table->n_of_cmds = g_cmd_table->n_of_cmds - 1;
	print_struct();
	executor_handler(envp);
	return (rtn);
}
