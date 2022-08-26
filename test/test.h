/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:31:04 by ghenaut-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/24 23:41:05 by ghenaut-         ###   ########.fr       */
=======
/*   Updated: 2022/08/23 22:48:09 by mvieira-         ###   ########.fr       */
>>>>>>> a09e60a317bb093cb2d7f91ab92c50b8146de697
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "../includes/minishell.h"

char	**tokenize(char **split_line, int size);
int	is_special(char *arg);
void	handle_special(char *line, t_list **lst);
<<<<<<< HEAD
void	init_global(char *envp[]);
=======
>>>>>>> a09e60a317bb093cb2d7f91ab92c50b8146de697
int check_quotes(const char *line);
char	*expand(char *line, int i);
void	expand_line(int i);
int	reset_global(int *rtn);

#endif