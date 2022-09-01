/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_regua.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:07:50 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/09/01 20:22:42 by ghenaut-         ###   ########.fr       */
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
/* NOT TESTING: 
	- signals
	- exit
	*/

char * envp[] = {
    "PATH=/home/GabrielHenaut/.asdf/shims:/opt/asdf-vm/bin:/home/GabrielHenaut/.local/bin:/home/GabrielHenaut/.cargo/bin:/home/GabrielHenaut/.asdf/installs/python/3.10.4/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Program Files/NVIDIA Corporation/NVIDIA NvDLISR:/mnt/c/Program Files/Docker/Docker/resources/bin:/mnt/c/ProgramData/DockerDesktop/version-bin:/mnt/c/Program Files/dotnet/:/mnt/c/Users/gabri/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/gabri/AppData/Local/Programs/Microsoft VS Code/bin:/home/GabrielHenaut/.dotnet/tools:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl",
    "P9K_SSH=0",
    "SHELL=/usr/bin/zsh",
};

Test(simple_command, bin_ls)
{
	char line[] = "/bin/ls > out1";
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line);
	executor_handler();
	int fd = open("out1", O_RDWR);
	char* rtn = get_next_line(fd);
	cr_expect(rtn != NULL, "/bin/ls works correctly");
	free_global();
	clear_memory();
	close(fd);
}

Test(simple_command, empty)
{
	char line[] = "> out2";
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line);
	executor_handler();
	int fd = open("out2", O_RDWR);
	char* rtn = get_next_line(fd);
	cr_expect(rtn == NULL, "empty works correctly");
	free_global();
	clear_memory();
	close(fd);
}

Test(simple_command_flags, bin_ls_la)
{
	char line[] = "/bin/ls -la > out3";
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line);
	executor_handler();
	int fd = open("out3", O_RDWR);
	char* rtn = get_next_line(fd);
	cr_expect(rtn != NULL, "/bin/ls -la returns NULL");
	cr_expect(strncmp(rtn, "total", 5) == 0, "/bin/ls return %s", rtn);
	free_global();
	clear_memory();
	close(fd);
}

Test(echo, echo_hello)
{
	char line[] = "echo \"hello\" > out4";
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line);
	executor_handler();
	int fd = open("out4", O_RDWR);
	char* rtn = get_next_line(fd);
	cr_expect(rtn != NULL, "echo returns NULL");
	cr_expect(strncmp(rtn, "hello\n", 6) == 0, "echo return %s, should be hello\n", rtn);
	free_global();
	clear_memory();
	close(fd);
}

Test(echo, echo_hello_big_text)
{
	char line[] = "echo \"hello Gabriel, how are you doing?\" > out5";
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line);
	executor_handler();
	int fd = open("out5", O_RDWR);
	char* rtn = get_next_line(fd);
	cr_expect(rtn != NULL, "echo returns NULL");
	cr_expect(strncmp(rtn, "hello Gabriel, how are you doing?\n", 34) == 0, "echo return %s, should be hello Gabriel, how are you doing?\n", rtn);
	free_global();
	clear_memory();
	close(fd);
}

Test(echo, echo_hello_n)
{
	char line[] = "echo -n \"hello\" > out6";
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line);
	executor_handler();
	int fd = open("out6", O_RDWR);
	char* rtn = get_next_line(fd);
	cr_expect(rtn != NULL, "echo returns NULL");
	cr_expect(strncmp(rtn, "hello\n", 6) != 0, "echo return %s, should be hello", rtn);
	cr_expect(strncmp(rtn, "hello", 5) == 0, "echo return %s, should be hello", rtn);
	free_global();
	clear_memory();
	close(fd);
}

Test(last_exit_code, code_0)
{
	char line[] = "ls -la > /dev/null";
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line);
	executor_handler();
	free_global();
	char line2[] = "echo $? > out7";
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line2);
	executor_handler();
	int fd = open("out7", O_RDWR);
	char* rtn = get_next_line(fd);
	cr_expect(strncmp(rtn, "0\n", 2) == 0, "$? return %s, should be 0", rtn);
	free_global();
	clear_memory();
	close(fd);
}

Test(last_exit_code, code_2)
{
	char line[] = "ls -la dasdasd > /dev/null";
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line);
	executor_handler();
	free_global();
	char line2[] = "echo $? > out8";
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	parse_line(line2);
	executor_handler();
	int fd = open("out8", O_RDWR);
	char* rtn = get_next_line(fd);
	cr_expect(strncmp(rtn, "2\n", 2) == 0, "$? return %s, should be 2", rtn);
	free_global();
	clear_memory();
	close(fd);
}

// Test(last_exit_code, code_sum)
// {
// 	char line[] = "ls -la dasdasd > /dev/null";
// 	init_global(envp);
// 	int garbage = 0;
// 	reset_global(&garbage);
// 	cr_expect(garbage == 0, "no malloc error");
// 	parse_line(line);
// 	executor_handler();
// 	free_global();
// 	char line2[] = "expr $? + $? > out9";
// 	reset_global(&garbage);
// 	cr_expect(garbage == 0, "no malloc error");
// 	parse_line(line2);
// 	cr_log_info("%s\n", g_cmd_table->table[0]);
// 	// executor_handler();
// 	// int fd = open("out9", O_RDWR);
// 	// char* rtn = get_next_line(fd);
// 	// cr_expect(strncmp(rtn, "4\n", 2) == 0, "$? return %s, should be 4", rtn);
// 	// free_global();
// 	// clear_memory();
// 	// close(fd);
// }

