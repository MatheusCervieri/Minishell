/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:31:04 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/20 00:54:58 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "../includes/minishell.h"

char	**expander(char **split_line);
int	is_special(char *arg);
void	handle_special(char *line, t_list **lst);
void	init_global(void);

#endif