/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:23:53 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/25 13:17:12 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char **argvwtf;
	argvwtf = malloc(sizeof(char *) * 7);
	argvwtf[0] = ft_strdup("pipex_bonus");
	argvwtf[1] = ft_strdup("infile");
	argvwtf[2] = ft_strdup("grep c");
	argvwtf[3] = ft_strdup("grep b");
	argvwtf[4] = ft_strdup("grep a");
	argvwtf[5] = ft_strdup("test4.txt");
	argvwtf[6] = ft_strdup("NULL");
	pipex(6, argvwtf, envp);
	int fd = open("./test4.txt", O_RDWR);
	char *buf = get_next_line(fd);
	printf("%s \n", buf);
	close(fd);
}