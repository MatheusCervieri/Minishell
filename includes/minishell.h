/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghosthologram <ghosthologram@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:24:39 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/13 19:19:47 by ghosthologr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd_table
{
	t_list	*table; //vai ser uma lista de listas, pois cada lista vai ter uma lista do comando com as suas flags e tals
	int		size;
}				t_cmd_table;

extern t_cmd_table *cmd_table;

int		init_shell(void);
int		parse_line(char *line);
void	free_split_line(char **split_line);
char	**expander(char **split_line);

#endif