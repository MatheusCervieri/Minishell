/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:24:39 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/30 17:54:16 by mvieira-         ###   ########.fr       */
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
	int		here_doc_loop;
	int		here_doc_file; 
	int		signal; 
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
	int		*pids;
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
void	child(t_pipex *data, char **envp);
void	close_pipes(t_pipex *data);

//Pipex 2.0 
void	init_pipes(t_pipex *data);
char	*find_path(char **envp);
void	here_doc(char *argv, t_pipex *pipex);


void	executor_handler(void);

//Built ins 
void	env_bi(char **cmd_args);
void	pwd_bi(void);
int		args_len(char **cmd_args);
void	cd_bi(char **cmd_args, char **envp);
void	echo_bi(char **cmd_args);
int		is_builtin(char *cmd);
void	export_bi(char **cmd_args);
void	remove_node(t_list **head, int position);
int		lst_find_var_p(t_list *head, char *var_name);
int	find_equal_position(char *arg);
void	change_node(t_list **head, int position, char *arg);
void	unset_bi(char **cmd_args);
void	exit_bi(void);
char	**convert_list_to_char(void);
void	signals_parent(void);
void	signals_child(void);
void	signals_here_doc(void);
char	*get_cmd(char **paths, char *cmd);
void	handle_dup(t_pipex *data);
void	execute_builtin(t_pipex *data, char *cmd, char **cmd_args, char **envp);
void	put_infile_fd(t_pipex *data, char *infile_path);
void	put_outfile_fd(t_pipex *data, char *outfile_path);
void	print_envp(char **envp);
void	print_export_no_parameters(char **envp);

t_list	*lexer(char **line);
void	minishell(char **envp);
int		parse_line(char *line);
void	free_split_line(char **split_line);
char	*join_with_space(char *str1, char *str2);
int		get_cmds(t_list *tct);
int		is_special(char *arg);
void	handle_special(char *line, t_list **lst);
char	**expander(char *line);
int		print_and_return(const char *msg, int err_code);
void	expand_env(void);
t_list	*make_list(char **envp);
void	clear_memory(void);
void	free_global(void);

#endif