/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:24:39 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/19 22:23:46 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// tirei o err file, pq aparentemente a gente nao tem que fazer a parte de mudar o stderr, e pra usar sempre o padrao

typedef struct s_cmd_table
{
	char 	**table;	// array com os comandos
	char	*infile;	// por padrao STDIN_FILENO, ou o nome do arquive se a pessoa mudar
	char	*outfile;	// por padrao STDOUT_FILENO, ou o nome do arquive se a pessoa mudar
	int		n_of_pipes; // numero de pipes
	int		n_of_cmds;	// numeros de comandos
	int		here_doc;	// 0 por padrao, 1 se a pessoa tiver usando here_doc
	char	*limiter;	// limeter para sair do here_doc
	int		append;		// 0 por padrao, 1 se a pessoa tiver especificado uma outfile e especificado append inves de sobreescrever
}				t_cmd_table;

extern t_cmd_table *cmd_table;

int		init_shell(void);
int		parse_line(char *line);
void	free_split_line(char **split_line);
char	**expander(char **split_line);
char	*join_with_space(char *str1, char *str2);

#endif