/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:31:04 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/21 20:59:56 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "../includes/minishell.h"

char	**tokenize(char **split_line, int size);
int	is_special(char *arg);
void	handle_special(char *line, t_list **lst);
void	init_global(void);
int check_quotes(const char *line);
char	*expand(char *line, int i);
void	expand_line(int i);

#endif