/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:24:39 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/23 22:18:31 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
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



typedef struct s_cmd_table
{
    char    **table;	// array com os comandos
	char	*infile;	// por padrao STDIN_FILENO, ou o nome do arquive se a pessoa mudar
	char	*outfile;	// por padrao STDOUT_FILENO, ou o nome do arquive se a pessoa mudar
	int		infile_exists; //0 se não existir 1 se exisitir (no caso é se < existir);
	int		outfile_exists; //0 se não existir 1 se existir (no caso é se > existir); 
	int		n_of_pipes; // numero de pipes
	int		n_of_cmds;	// numeros de comandos
	int		here_doc;	// 0 por padrao, 1 se a pessoa tiver usando here_doc
	char	*limiter;	// limeter para sair do here_doc
	int		append; // 0 por padrao, 1 se a pessoa tiver especificado uma outfile e especificado append inves de sobreescrever
	int		status;
	int		last_status;
	t_list	*envp;		
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
	char	*limiter;
	int		append; 
	pid_t	pid;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		*pipe;
	int		idx;
	int		success;
}				t_pipex;

extern t_cmd_table *g_cmd_table;

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
void	here_doc(char *argv, t_pipex *pipex);


int	init_shell(char **envp);
void	executor_handler(void);

//Built ins 
void env_bi(char **cmd_args, char **envp);
void pwd_bi(void);
int args_len(char **cmd_args);
void cd_bi(char **cmd_args, char **envp);
void echo_bi(char **cmd_args);
int is_builtin(char *cmd);
void execute_builtin(char *cmd, char **cmd_args, char **envp);
int	init_global(void);
void export_bi(char **cmd_args);
void	remove_node(t_list **head, int position);
int	lst_find_var_p(t_list *head, char *var_name);
void	change_node(t_list **head, int position, char *arg);
void unset_bi(char **cmd_args);
void	print_list(t_list *list);
void    exit_bi(char **cmd_args);
char	**convert_list_to_char(t_list *head);


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