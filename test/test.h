/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:31:04 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/31 15:30:17 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "../includes/minishell.h"

char	**tokenize(char **split_line, int size);
int	is_special(char *arg);
void	handle_special(char *line, t_list **lst);
int check_quotes(const char *line);
char	*expand(char *line, int i);
void	expand_line(int i);
int	init_global(char *envp[]);
int	reset_global(int *rtn);

#endif