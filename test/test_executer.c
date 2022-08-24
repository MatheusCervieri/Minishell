/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:11 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/23 23:47:52 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <criterion/new/assert.h>
#include <criterion/criterion.h>
#include "../includes/minishell.h"
#include <string.h>

// Test(function you are testing, test name){
// 	test...
// }





Test(executer_handler, PRIMEIRO_TESTE)
{
	printf("< text1.txt grep hello | cat -e > out \n");
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

	char line[] = "< text1.txt grep hello | cat -e > out";
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	init_global();
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	int rtn = parse_line(line);
	cr_expect(rtn == 0, "parse_line returns correctly");
	
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();
	int fd = open("./out", O_RDONLY);
	char *lineout = get_next_line(fd);
	cr_expect(strcmp(lineout, "hello$\n") == 0, "in file is correct");
	
}

Test(executer_handler, ls_errado)
{
	printf("ls dasdsadas > out");
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

	char line[] = "ls dasdsadas > out";
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	init_global();
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	int rtn = parse_line(line);
	cr_expect(rtn == 0, "parse_line returns correctly");
	cr_expect(strcmp(g_cmd_table->table[0], "ls dasdsadas") == 0, "%s the comand is", g_cmd_table->table[0]);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();
	int fd = open("./out", O_RDONLY);
	char *lineout = get_next_line(fd);
	cr_expect(g_cmd_table->status == 2, "%i STATUS", g_cmd_table->status);
	//cr_expect(strcmp(lineout, "hello$\n") == 0, "in file is correct");
	
}
