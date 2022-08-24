/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:23:53 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/24 11:47:31 by mvieira-         ###   ########.fr       */
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
    int	rtn;
	char *line;
	rtn = 0;

	line = ft_strdup("< infile grep c | grep a | grep t > test4.txt");
	init_global();
	reset_global(&rtn);
	rtn = 0;
	rtn = parse_line(line);
	//g_cmd_table->infile_exists = 0;
	//g_cmd_table->outfile_exists = 0;
    g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
 
	executor_handler();

	return (rtn);
    /*
	char line[] = "< infile grep c | grep a | grep t > test4.txt";
	init_global();
	int garbage = 0;
	reset_global(&garbage);
	int rtn = parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();
    
	int fd = open("./test4.txt", O_RDONLY);
	char *lineout = get_next_line(fd);
	int fd2 = open("./test4original.txt", O_RDONLY);
	char *lineout2 = get_next_line(fd2);
	if (g_cmd_table->status == 0)
        printf("Status: %i , is correct \n", g_cmd_table->status);
    if(strcmp(lineout, lineout2) == 0)
        printf("Outfile is correct");

	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
	free(lineout);
	free(lineout2);
	close(fd);
	close(fd2);
    */
    
}