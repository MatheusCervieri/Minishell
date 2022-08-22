/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:24:39 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/21 22:46:09 by ghenaut-         ###   ########.fr       */
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
	char	**table;	
	char	*infile;	
	char	*outfile;	
	int		n_of_pipes;
	int		n_of_cmds;	
	int		here_doc;	
	char	*limiter;	
	int		append;		
	int		status;
	int		last_status;
}				t_cmd_table;

extern t_cmd_table	*g_cmd_table;

t_list	*lexer(char **line);
int		minishell(void);
int		parse_line(char *line);
void	free_split_line(char **split_line);
char	*join_with_space(char *str1, char *str2);
int		get_cmds(t_list *tct);
int		is_special(char *arg);
void	handle_special(char *line, t_list **lst);
char	**expander(char *line);
int		print_and_return(const char *msg, int err_code);
void	expand_env(void);

#endif