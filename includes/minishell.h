/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:24:39 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/18 13:15:37 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>


typedef struct s_cmd_table
{
    char    **comands_string;	// array com os comandos
	char	*infile;	// por padrao STDIN_FILENO, ou o nome do arquive se a pessoa mudar
	char	*outfile;	// por padrao STDOUT_FILENO, ou o nome do arquive se a pessoa mudar
	int		infile_exists; //0 se não existir 1 se exisitir;
	int		outfile_exists; //0 se não existir 1 se existir; 
	int		n_of_pipes; // numero de pipes
	int		n_of_cmds;	// numeros de comandos
	int		here_doc;	// 0 por padrao, 1 se a pessoa tiver usando here_doc
	char	*limiter;	// limeter para sair do here_doc
	int		append;		// 0 por padrao, 1 se a pessoa tiver especificado uma outfile e especificado append inves de sobreescrever
}				t_cmd_table;


typedef struct s_pipex
{
	int		infile;
	int		outfile;
    int     infile_exists;
    int     outfile_exists;
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	int		here_doc;
	int		append; 
	pid_t	pid;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		*pipe;
	int		idx;
	int		success;
}				t_pipex;

t_cmd_table g_cmd_table;

//hadle_file.c
void	get_outfile(char *argv, t_pipex *data);
void	get_infile(char **argv, t_pipex *data);

//error.c
void	msg_error(char *error, int exit_code);
void	parent_close(t_pipex *data, char *error, int exit_code);
void	pipe_free(t_pipex *data, char *error, int exit_code);
void	close_io_exit(t_pipex *data, char *error, int exit_code);
void	free_cmd(t_pipex *data);

//init_data.c
void	init_data(t_pipex *data, int argc, char *envp[]);

//child.c
void	child(t_pipex data, char **envp);
void	close_pipes(t_pipex *data);

//Pipex 2.0 
void	init_pipes(t_pipex *data);
char	*find_path(char **envp);


int	init_shell(char **envp);
void executor_handler(char **envp);


#endif