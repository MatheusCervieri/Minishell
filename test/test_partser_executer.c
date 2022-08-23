/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_partser_executer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:11 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/22 22:31:16 by mvieira-         ###   ########.fr       */
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
	char *line[] = {"grep", "hello"};
	t_list *rtn = lexer(line);
	cr_expect(rtn != NULL, "parse_line returns something");
}
