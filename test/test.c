/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghosthologram <ghosthologram@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:11 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/15 13:55:12 by ghosthologr      ###   ########.fr       */
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