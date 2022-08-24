/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:11 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/24 16:55:51 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <criterion/new/assert.h>
#include <criterion/criterion.h>
#include "../includes/minishell.h"
#include <string.h>

Test(executer_handler, test5_just_one_comand)
{
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

	char line[] = "ls >> test5.txt";
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
	
	int fd = open("./test5.txt", O_RDONLY);
	char *lineout = get_next_line(fd);
	int fd2 = open("./test5original.txt", O_RDONLY);
	char *lineout2 = get_next_line(fd2);
	cr_expect(g_cmd_table->status == 0, "%i STATUS", g_cmd_table->status);
	cr_expect(strcmp(lineout, lineout2) == 0, "out file is correct");
	
	
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
	free(lineout);
	free(lineout2);
	close(fd);
	close(fd2);
}

Test(executer_handler, test2_two_comands_without_infile)
{
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

	char line[] = "ls | grep a >> test2.txt";
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
	
	int fd = open("./test2.txt", O_RDONLY);
	char *lineout = get_next_line(fd);
	int fd2 = open("./test2original.txt", O_RDONLY);
	char *lineout2 = get_next_line(fd2);
	cr_expect(g_cmd_table->status == 0, "%i STATUS", g_cmd_table->status);
	cr_expect(strcmp(lineout, lineout2) == 0, "out file is correct");
	
	
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
	free(lineout);
	free(lineout2);
	close(fd);
	close(fd2);
}

Test(executer_handler, test3_tree_comands_without_infile)
{
	/* O output está correto, mas tem algum erro  */
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

	char line[] = "ls | grep a | grep t >> test3.txt";
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
	int fd = open("./test3.txt", O_RDONLY);
	char *lineout = get_next_line(fd);
	int fd2 = open("./test3original.txt", O_RDONLY);
	char *lineout2 = get_next_line(fd2);
	cr_expect(g_cmd_table->status == 0, "%i STATUS", g_cmd_table->status);
	cr_expect(strcmp(lineout, lineout2) == 0, "out file is correct");

	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
	free(lineout);
	free(lineout2);
	close(fd);
	close(fd2);
}


Test(executer_handler, test4_test4_tree_comands_with_infile)
{
	/* O output está correto, mas tem algum erro  */
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

	char line[] = "< infile grep c | grep a | grep t >> test4.txt";
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
	int fd = open("./test4.txt", O_RDONLY);
	char *lineout = get_next_line(fd);
	int fd2 = open("./test4original.txt", O_RDONLY);
	char *lineout2 = get_next_line(fd2);
	cr_expect(g_cmd_table->status == 0, "%i STATUS", g_cmd_table->status);
	cr_expect(strcmp(lineout, lineout2) == 0, "out file is correct");

	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
	free(lineout);
	free(lineout2);
	close(fd);
	close(fd2);
}

/*
ENV PROBLEM WHEN INTERACTING WITH OTHER PROGRAMS!
Test(executer_handler_built_in, test6_env_build_in_two_comands_append)
{

	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

	char line[] = "env | grep a >> test6.txt";
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	init_global();
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	int rtn = parse_line(line);
	cr_expect(rtn == 0, "parse_line returns correctly");
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	print_struct();
	executor_handler();
	int fd = open("./test6.txt", O_RDONLY);
	char *lineout = get_next_line(fd);
	int fd2 = open("./test6original.txt", O_RDONLY);
	char *lineout2 = get_next_line(fd2);
	cr_expect(g_cmd_table->status == 0, "%i STATUS", g_cmd_table->status);
	cr_expect(strcmp(lineout, lineout2) == 0, "out file is correct");

	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
	free(lineout);
	free(lineout2);
	close(fd);
	close(fd2);
}
*/


Test(executer_handler_built_in, test7_pwd_build_in_two_comands_append)
{

	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

	char line[] = "pwd | grep a >> test7.txt";
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	init_global();
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	int rtn = parse_line(line);
	cr_expect(rtn == 0, "parse_line returns correctly");
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	print_struct();
	executor_handler();
	int fd = open("./test7.txt", O_RDONLY);
	char *lineout = get_next_line(fd);
	int fd2 = open("./test7original.txt", O_RDONLY);
	char *lineout2 = get_next_line(fd2);
	cr_expect(g_cmd_table->status == 0, "%i STATUS", g_cmd_table->status);
	cr_expect(strcmp(lineout, lineout2) == 0, "out file is correct");

	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
	free(lineout);
	free(lineout2);
	close(fd);
	close(fd2);
}