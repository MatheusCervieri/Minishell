/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:23:53 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/25 17:05:59 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
int    main(int argc, char **argv, char **envp)
{
    int    rtn;

    rtn = 0;
    rtn = minishell();
    return (rtn);
}
*/
int    main(int argc, char **argv, char **envp)
{
	
	printf("%s, %i \n", argv[0], argc);
	
	/*
	Estou com dois problemas:
	< infile grep a ;
	ls > teste.txt
	Ou seja infile e outfile apenas com um comando. 
	*/
	
	int	rtn;
	char *line;
	rtn = 0;
	line = ft_strdup("ls > teste.txt");
	init_global();
	reset_global(&rtn);
	rtn = 0;
	rtn = parse_line(line);
    g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();
	

	/*	
	printf("Test 10\n");
	int	rtn;
	char *line;
	rtn = 0;
	line = ft_strdup("< infile grep c | grep a | grep t > test10.txt");
	init_global();
	reset_global(&rtn);
	rtn = 0;
	rtn = parse_line(line);
    g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();
	printf("END: Test 10 \n");
	printf("Test 1\n");
	line = ft_strdup("ls > test1.txt");
	reset_global(&rtn);
	rtn = parse_line(line);
	executor_handler();
	printf("END: Test 1\n");
	printf("Test 2\n");
	line = ft_strdup("ls | grep a > test2.txt");
	reset_global(&rtn);
	rtn = parse_line(line);
	executor_handler();
	printf("END: Test 2\n");
	printf("Test 3\n");
	line = ft_strdup("ls | grep a | grep t > test3.txt");
	reset_global(&rtn);
	rtn = parse_line(line);
	executor_handler();
	printf("END: Test 3\n");
	printf("Test 4\n");
	line = ft_strdup("< infile grep c | grep a | grep t > test4.txt");
	reset_global(&rtn);
	rtn = parse_line(line);
	executor_handler();
	printf("END: Test 4\n");
	printf("Test 5\n");
	line = ft_strdup("ls >> test5.txt");
	reset_global(&rtn);
	rtn = parse_line(line);
	executor_handler();
	printf("END: Test 5\n");
	
	
	printf("Test 11\n");
	line = ft_strdup("< infile ls | grep a > test11.txt");
	reset_global(&rtn);
	rtn = parse_line(line);
	executor_handler();
	printf("END: Test 11\n");
	//printf("Test 12\n");
	//line = ft_strdup("< infile ls | grep a");
	//reset_global(&rtn);
	//rtn = parse_line(line);
	//executor_handler();
	printf("END: Test 12\n");
	printf("Test 13 \n");
	line = ft_strdup("ls | grep a > test13.txt");
	reset_global(&rtn);
	rtn = parse_line(line);
	executor_handler();
	printf("END: Test 13 \n");
	printf("Test 14 \n");
	line = ft_strdup("ls > test14.txt");
	reset_global(&rtn);
	rtn = parse_line(line);
	executor_handler();
	printf("END: Test 14 \n");
	*/
	return(rtn);
	

    
}