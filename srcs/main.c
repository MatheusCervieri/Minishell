/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:23:53 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/22 12:00:54 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int	main(int argc, char **argv, char **envp)
{
	int	rtn;

	rtn = init_shell(envp);
	return (rtn);
}
*/

/*
typedef struct s_cmd_table
{
	typedef struct s_cmd_table
{
    char    **comands_string;	// array com os comandos
	char	*infile;	// por padrao STDIN_FILENO, ou o nome do arquive se a pessoa mudar
	char	*outfile;	// por padrao STDOUT_FILENO, ou o nome do arquive se a pessoa mudar
	int		n_of_pipes; // numero de pipes
	int		n_of_cmds;	// numeros de comandos
	int		here_doc;	// 0 por padrao, 1 se a pessoa tiver usando here_doc
	char	*limiter;	// limeter para sair do here_doc
	int		append;		// 0 por padrao, 1 se a pessoa tiver especificado uma outfile e especificado append inves de sobreescrever
}				t_cmd_table;
*/



int	main(int argc, char **argv, char **envp)
{
	char **cmd_args;
	cmd_args = malloc(sizeof(char *) * 4);
	cmd_args[0] = ft_strdup("echo");
	cmd_args[1] = ft_strdup("-n");
	cmd_args[2] = ft_strdup("dasdsadasdasdas");
	cmd_args[3] = ft_strdup("dasdsadasdasdas");
	echo_bi(cmd_args);
/*
	char **comands_string;
	comands_string = malloc(sizeof(char*) * 3);
	comands_string[0] = ft_strdup("env");
	comands_string[1] = ft_strdup("grep a");
	comands_string[2] = ft_strdup("grep SHELL");
	g_cmd_table.comands_string = comands_string;
	g_cmd_table.n_of_cmds = 3;
	g_cmd_table.infile = ft_strdup("text1.txt");
	g_cmd_table.outfile = ft_strdup("text8.txt");
	g_cmd_table.infile_exists = 1;
	g_cmd_table.outfile_exists = 1;
	g_cmd_table.here_doc = 0;
	g_cmd_table.append = 1;
	g_cmd_table.limiter = ft_strdup("teste");
	executor_handler(envp);
	free(g_cmd_table.infile);
	free(g_cmd_table.outfile);
	free(g_cmd_table.limiter);
	free(comands_string[0]);
	free(comands_string[1]);
	free(comands_string[2]);
	free(comands_string);
*/
}
