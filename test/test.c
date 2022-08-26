/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:11 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/26 12:05:09 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <criterion/new/assert.h>
#include <criterion/criterion.h>
#include "../includes/minishell.h"
#include <string.h>

Test(executer_handler, test1_test)
{

	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

	//char *line = ft_strdup("ls > test1.txt");
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	char *line = ft_strdup("ls > test1.txt");
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(envp);
	executor_handler();
	cr_expect(g_cmd_table->last_status == 0, "Exit code is correct");
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
}

Test(executer_handler, test2_test)
{
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;
	
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	char *line = ft_strdup("ls | grep a > test2.txt");
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(envp);
	executor_handler();
	cr_expect(g_cmd_table->last_status == 0, "Exit code is correct");
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);

}

Test(executer_handler, test3_test)
{
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;
	
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	char *line;
	line = ft_strdup("ls | grep a | grep t > test3.txt");
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(envp);
	executor_handler();
	cr_expect(g_cmd_table->last_status == 0, "Exit code is correct");
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);

}

Test(executer_handler, test4_test)
{
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;
	
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	char *line;
	line = ft_strdup("< infile grep c | grep a | grep t > test4.txt");
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(envp);
	executor_handler();
	cr_expect(g_cmd_table->last_status == 0, "Exit code is correct");
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
}

Test(executer_handler, test5_test)
{
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;
	
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	char *line;
	line = ft_strdup("ls >> test5.txt");
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(envp);
	executor_handler();
	cr_expect(g_cmd_table->last_status == 0, "Exit code is correct");
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
}
/*
Test(executer_handler_built_in, test6_test)
{
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;
	
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	char *line;
	line = ft_strdup("env | grep a >> test6.txt");
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(envp);
	executor_handler();
	cr_expect(g_cmd_table->last_status == 0, "Exit code is correct");
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
}

Test(executer_handler_built_in, test7_test)
{
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;
	
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	char *line;
	line = ft_strdup("pwd | grep a >> test7.txt");
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(envp);
	executor_handler();
	cr_expect(g_cmd_table->last_status == 0, "Exit code is correct");
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
}

*/
Test(executer_handler_built_in, test8_test)
{
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;
	
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	char *line;
	line = ft_strdup("echo dasdasdsa >> test8.txt");
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(envp);
	executor_handler();
	cr_expect(g_cmd_table->last_status == 0, "Exit code is correct");
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
}


