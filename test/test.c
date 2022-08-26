/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:11 by ghenaut-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/25 00:41:44 by ghenaut-         ###   ########.fr       */
=======
/*   Updated: 2022/08/25 18:11:02 by mvieira-         ###   ########.fr       */
>>>>>>> a09e60a317bb093cb2d7f91ab92c50b8146de697
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <criterion/new/assert.h>
#include <criterion/criterion.h>
#include "../includes/minishell.h"
#include <string.h>

<<<<<<< HEAD
// Test(function you are testing, test name){
// 	test...
// }

char * envp[] = {
    "PATH=/home/GabrielHenaut/.asdf/shims:/opt/asdf-vm/bin:/home/GabrielHenaut/.local/bin:/home/GabrielHenaut/.cargo/bin:/home/GabrielHenaut/.asdf/installs/python/3.10.4/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Program Files/NVIDIA Corporation/NVIDIA NvDLISR:/mnt/c/Program Files/Docker/Docker/resources/bin:/mnt/c/ProgramData/DockerDesktop/version-bin:/mnt/c/Program Files/dotnet/:/mnt/c/Users/gabri/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/gabri/AppData/Local/Programs/Microsoft VS Code/bin:/home/GabrielHenaut/.dotnet/tools:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl",
    "P9K_SSH=0",
    "SHELL=/usr/bin/zsh",
};

Test(lexer, return_something)
{
	char *line[] = {"grep", "hello"};
	t_list *rtn = lexer(line);
	cr_expect(rtn != NULL, "parse_line returns something");
}

Test(lexer, rtn_correct)
{	
	char *line[] = {"grep", "hello"};
	t_list *rtn = lexer(line);
	cr_expect(strcmp(((char *)rtn->content), "grep") == 0, "parse_line returns correctly");
	cr_expect(strcmp(((char *)rtn->next->content), "hello") == 0, "parse_line returns correctly");
	cr_expect(rtn->next->next == NULL, "parse_line returns correctly");
}

Test(expander, rtn_something)
{
	char tmp[] = "hello world";
	char **rtn = expander(tmp);
	cr_expect(*rtn != NULL, "expender returns something");
}

Test(expander, rtn_c_no_quotes)
{
	char tmp[] = "hello world";
	char **rtn = expander(tmp);
	cr_expect(strcmp(rtn[0], "hello") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[1], "world") == 0, "expander returns correctly");
	cr_expect(rtn[2] == NULL, "expander returns correctly");
}

Test(expander, rtn_c_with_quotes)
{
	char tmp[] = "grep 'hello world'";
	char **rtn = expander(tmp);
	cr_expect(strcmp(rtn[0], "grep") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[1], "'hello world'") == 0, "expander returns correctly");
	cr_expect(rtn[2] == NULL, "expander returns correctly");
}

Test(expander, rtn_c_with_2_quotes)
=======
Test(executer_handler, test1_test)
>>>>>>> a09e60a317bb093cb2d7f91ab92c50b8146de697
{

	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;

<<<<<<< HEAD
Test(is_special, rtn_c_not_special)
{
	char tmp[] = "grep";
	int rtn = is_special(tmp);
	cr_expect(rtn == 0, "is_special returns correctly");
}

Test(is_special, rtn_c_special)
{
	char tmp[] = "<";
	int rtn = is_special(tmp);
	cr_expect(rtn == 1, "is_special returns correctly");
}

Test(is_special, rtn_c_special_2)
{
	char tmp[] = "<<";
	int rtn = is_special(tmp);
	cr_expect(rtn == 1, "is_special returns correctly");
}

Test(parse_line, return_c)
{
	char line[] = "< in grep hello | cat | ls -la > out";
	init_global(envp);
=======
	char *line = ft_strdup("ls > test1.txt");
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	init_global();
>>>>>>> a09e60a317bb093cb2d7f91ab92c50b8146de697
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();

<<<<<<< HEAD
Test(parse_line, return_c_2)
{
	char line[] = "<< LIMITER grep hello | cat -e | ls -la >> out";
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	int rtn = parse_line(line);
	cr_expect(rtn == 0, "parse_line returns correctly");
	cr_expect(strcmp(g_cmd_table->infile, "STDIN_FILENO") == 0, "in file is correct");
	cr_expect(strcmp(g_cmd_table->limiter, "LIMITER") == 0, "limiter is correct");
	cr_expect(strcmp(g_cmd_table->outfile, "out") == 0, "out file is correct");
	cr_expect(g_cmd_table->here_doc == 1, "here_doc is correct");
	cr_expect(g_cmd_table->append == 1, "append is correct");
	cr_expect(g_cmd_table->n_of_cmds == 3, "n_of_cmds is %d", g_cmd_table->n_of_cmds);
	cr_expect(strcmp(g_cmd_table->table[0], "grep hello") == 0, "cmd 1 is correct");
	cr_expect(strcmp(g_cmd_table->table[1], "cat -e") == 0, "cmd 2 is %s", g_cmd_table->table[1]);
	cr_expect(strcmp(g_cmd_table->table[2], "ls -la") == 0, "cmd 3 is correct");
	cr_expect(g_cmd_table->table[3] == NULL, "cmd 4 is %s", g_cmd_table->table[3]);
}
=======
	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);
>>>>>>> a09e60a317bb093cb2d7f91ab92c50b8146de697

}

Test(executer_handler, test2_test)
{
<<<<<<< HEAD
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	g_cmd_table->last_status = 0;
	g_cmd_table->table = malloc(sizeof(char *) * 3);
	g_cmd_table->table[0] = ft_strdup("$?");
	char *rtn = expand(g_cmd_table->table[0], 0);
	cr_expect(strcmp(rtn, "0") == 0, "expand returns %s", rtn);
}

Test(expand, return_c_var)
{
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	g_cmd_table->table = malloc(sizeof(char *) * 3);
	g_cmd_table->table[0] = ft_strdup("$SHELL");
	char *rtn = expand(g_cmd_table->table[0], 0);
	cr_expect(strcmp(rtn, "/usr/bin/zsh") == 0, "expand returns correctly");
}

Test(expand, return_c_var_in_quotes)
{
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	g_cmd_table->table = malloc(sizeof(char *) * 3);
	g_cmd_table->table[0] = ft_strdup("echo \"$SHELL\"");
	char *rtn = expand(g_cmd_table->table[0], 0);
	cr_expect(strcmp(rtn, "/usr/bin/zsh") == 0, "expand returns %s correctly", rtn);
}

Test(expand, return_c_invalid_var)
{
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	g_cmd_table->table = malloc(sizeof(char *) * 3);
	g_cmd_table->table[0] = ft_strdup("$INVALID");
	char *rtn = expand(g_cmd_table->table[0], 0);
	cr_expect(strcmp(rtn, "") == 0, "expand returns %s", rtn);
}

Test(expand, return_c_no_var)
{
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	g_cmd_table->last_status = 0;
	g_cmd_table->table = malloc(sizeof(char *) * 3);
	g_cmd_table->table[0] = ft_strdup("$");
	char *rtn = expand(g_cmd_table->table[0], 0);
	cr_expect(strcmp(rtn, "$") == 0, "expand returns %s", rtn);
}

Test(expand_env, return_c_exit_code)
{
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	g_cmd_table->last_status = 0;
	g_cmd_table->table = malloc(sizeof(char *) * 3);
	g_cmd_table->table[0] = ft_strdup("$?");
	expand_env();
	cr_expect(strcmp(g_cmd_table->table[0], "0") == 0, "expand_env returns %s", g_cmd_table->table[0]);
}

Test(expand_env, return_c_var)
{
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	g_cmd_table->table = malloc(sizeof(char *) * 3);
	g_cmd_table->table[0] = ft_strdup("$SHELL");
	expand_env();
	cr_expect(strcmp(g_cmd_table->table[0], "/usr/bin/zsh") == 0, "expand_env returns %s", g_cmd_table->table[0]);
}

Test(expand_env, return_c_var_in_dquotes)
{
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	g_cmd_table->table = malloc(sizeof(char *) * 3);
	g_cmd_table->table[0] = ft_strdup("'\"$SHELL\"'");
	expand_env();
	cr_expect(strcmp(g_cmd_table->table[0], "'\"$SHELL\"'") == 0, "expand_env returns %s", g_cmd_table->table[0]);
}


Test(expand_env, return_c_var_in_squotes)
{
	init_global(envp);
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	g_cmd_table->table = malloc(sizeof(char *) * 3);
	g_cmd_table->table[0] = ft_strdup("\"'$SHELL'\"");
	expand_env();
	cr_expect(strcmp(g_cmd_table->table[0], "\"'/usr/bin/zsh'\"") == 0, "expand_env returns %s", g_cmd_table->table[0]);
}
=======
	char **envp;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("PATH=/home/matheuscervieri/.vscode-server/bin/e4503b30fc78200f846c62cf8091b76ff5547662/bin/remote-cli:/home/matheuscervieri/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Users/mathc/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/mathc/AppData/Roaming/npm:/mnt/c/Users/mathc/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin");
	envp[1] = ft_strdup("HOSTTYPE=x86_64");
	envp[2] = ft_strdup("PULSE_SERVER=/mnt/wslg/PulseServer");
	envp[3] = NULL;
	
	char *line = ft_strdup("ls | grep a > test2.txt");
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	init_global();
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();

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
	
	char *line;
	line = ft_strdup("ls | grep a | grep t > test3.txt");
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	init_global();
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();

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
	
	char *line;
	line = ft_strdup("< infile grep c | grep a | grep t > test4.txt");
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	init_global();
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();
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
	
	char *line;
	line = ft_strdup("ls >> test5.txt");
	g_cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	init_global();
	int garbage = 0;
	reset_global(&garbage);
	parse_line(line);
	g_cmd_table->envp = ft_lstnew((char *)envp[0]);
	make_list(&(g_cmd_table->envp), envp);
	executor_handler();

	free(envp[0]);
	free(envp[1]);
	free(envp[2]);
	free(envp[3]);
	free(envp);

}



>>>>>>> a09e60a317bb093cb2d7f91ab92c50b8146de697
