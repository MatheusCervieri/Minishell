/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:11 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/25 00:41:44 by ghenaut-         ###   ########.fr       */
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
{
	char tmp[] = "grep 'hello world' 'asdasd asdasd'";
	char **rtn = expander(tmp);
	cr_expect(strcmp(rtn[0], "grep") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[1], "'hello world'") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[2], "'asdasd asdasd'") == 0, "expander returns correctly");
	cr_expect(rtn[3] == NULL, "expander returns correctly");
}

Test(expander, rtn_c_with_everything)
{
	char tmp[] = "< in grep \"hello\" | cat -e | ls -la > out";
	char **rtn = expander(tmp);
	cr_expect(strcmp(rtn[0], "<") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[1], "in") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[2], "grep") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[3], "\"hello\"") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[4], "|") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[5], "cat") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[6], "-e") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[7], "|") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[8], "ls") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[9], "-la") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[10], ">") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[11], "out") == 0, "expander returns correctly");
}

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
	int garbage = 0;
	reset_global(&garbage);
	cr_expect(garbage == 0, "no malloc error");
	int rtn = parse_line(line);
	cr_expect(rtn == 0, "parse_line returns correctly");
	cr_expect(strcmp(g_cmd_table->infile, "in") == 0, "in file is correct");
	cr_expect(strcmp(g_cmd_table->outfile, "out") == 0, "out file is correct");
	cr_expect(g_cmd_table->n_of_cmds == 3, "n_of_cmds is %d", g_cmd_table->n_of_cmds);
	cr_expect(strcmp(g_cmd_table->table[0], "grep hello") == 0, "cmd 1 is correct");
	cr_expect(strcmp(g_cmd_table->table[1], "cat") == 0, "cmd 2 is correct");
	cr_expect(strcmp(g_cmd_table->table[2], "ls -la") == 0, "cmd 3 is correct");
	cr_expect(g_cmd_table->table[3] == NULL, "cmd 4 is %s", g_cmd_table->table[3]);
}

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

Test(check_quotes, rtn_c_balanced)
{
	char tmp[] = "grep 'hello'";
	int rtn = check_quotes(tmp);
	cr_expect(rtn == 0, "check_quotes returns correctly");
}

Test(check_quotes, rtn_c_unbalanced)
{
	char tmp[] = "grep 'hello";
	int rtn = check_quotes(tmp);
	cr_expect(rtn == 1, "check_quotes returns correctly");
}

Test(expand, return_c_exit_code)
{
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