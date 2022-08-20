/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:11 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/19 23:12:49 by ghenaut-         ###   ########.fr       */
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

Test(lexer, return_something)
{
	char line[] = "grep hello";
	t_list *rtn = lexer(line);
	cr_expect(rtn != NULL, "parse_line returns something");
}

Test(lexer, rtn_correct)
{	
	char line[] = "grep hello";
	t_list *rtn = lexer(line);
	cr_expect(strcmp(((char *)rtn->content), "grep") == 0, "parse_line returns correctly");
	cr_expect(strcmp(((char *)rtn->next->content), "hello") == 0, "parse_line returns correctly");
	cr_expect(rtn->next->next == NULL, "parse_line returns correctly");
}

Test(lexer, rtn_correct_2)
{	
	char line[] = "echo 'hello world'";
	t_list *rtn = lexer(line);
	cr_expect(strcmp(((char *)rtn->content), "echo") == 0, "parse_line returns correctly");
	cr_expect(strcmp(((char *)rtn->next->content), "'hello world'") == 0, "parse_line returns correctly");
	cr_expect(rtn->next->next == NULL, "parse_line returns correctly");
}

Test(expander, rtn_something)
{
	char tmp[] = "hello world";
	char **line = ft_split(tmp, ' ');
	char **rtn = expander(line);
	cr_expect(*rtn != NULL, "expender returns something");
}

Test(expander, rtn_c_no_quotes)
{
	char tmp[] = "hello world";
	char **line = ft_split(tmp, ' ');
	char **rtn = expander(line);
	cr_expect(strcmp(rtn[0], "hello") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[1], "world") == 0, "expander returns correctly");
	cr_expect(rtn[2] == NULL, "expander returns correctly");
}

Test(expander, rtn_c_with_quotes)
{
	char tmp[] = "grep 'hello world'";
	char **line = ft_split(tmp, ' ');
	char **rtn = expander(line);
	cr_expect(strcmp(rtn[0], "grep") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[1], "'hello world'") == 0, "expander returns correctly");
	cr_expect(rtn[2] == NULL, "expander returns correctly");
}

Test(expander, rtn_c_with_2_quotes)
{
	char tmp[] = "grep 'hello world' 'asdasd asdasd'";
	char **line = ft_split(tmp, ' ');
	char **rtn = expander(line);
	cr_expect(strcmp(rtn[0], "grep") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[1], "'hello world'") == 0, "expander returns correctly");
	cr_expect(strcmp(rtn[2], "'asdasd asdasd'") == 0, "expander returns correctly");
	cr_expect(rtn[3] == NULL, "expander returns correctly");
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
	char line[] = "< in grep hello | cat -e | ls -la > out";
	int rtn = parse_line(line);
	cr_expect(rtn == 0, "parse_line returns correctly");
	cr_expect(strcmp(cmd_table->infile, "in") == 0, "in file is correct");
	cr_expect(strcmp(cmd_table->outfile, "out") == 0, "out file is correct");
	cr_expect(strcmp(cmd_table->table[0], "grep hello") == 0, "cmd 1 is correct");
	cr_expect(strcmp(cmd_table->table[1], "cat -e") == 0, "cmd 2 is correct");
	cr_expect(strcmp(cmd_table->table[2], "ls -la") == 0, "cmd 3 is correct");
	printf("%s\n", cmd_table->outfile);
}

Test(parse_line, return_c_2)
{
	char line[] = "<< LIMITER grep hello | cat -e | ls -la >> out";
	int rtn = parse_line(line);
	cr_expect(rtn == 0, "parse_line returns correctly");
	cr_expect(strcmp(cmd_table->infile, "STDIN_FILENO") == 0, "in file is correct");
	cr_expect(strcmp(cmd_table->limiter, "LIMITER") == 0, "limiter is correct");
	cr_expect(strcmp(cmd_table->outfile, "out") == 0, "out file is correct");
	cr_expect(cmd_table->here_doc == 1, "here_doc is correct");
	cr_expect(cmd_table->append == 1, "append is correct");
	cr_expect(strcmp(cmd_table->table[0], "grep hello") == 0, "cmd 1 is correct");
	cr_expect(strcmp(cmd_table->table[1], "cat -e") == 0, "cmd 2 is correct");
	cr_expect(strcmp(cmd_table->table[2], "ls -la") == 0, "cmd 3 is correct");
	printf("%s\n", cmd_table->outfile);
}