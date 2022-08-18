/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:16:27 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/18 11:19:07 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
typedef struct s_cmd_table
{
	char 	***table;	// array com os comandos
	char	*infile;	// por padrao STDIN_FILENO, ou o nome do arquive se a pessoa mudar
	char	*outfile;	// por padrao STDOUT_FILENO, ou o nome do arquive se a pessoa mudar
	int		n_of_pipes; // numero de pipes
	int		n_of_cmds;	// numeros de comandos
	int		here_doc;	// 0 por padrao, 1 se a pessoa tiver usando here_doc
	char	*limiter;	// limeter para sair do here_doc
	int		append;		// 0 por padrao, 1 se a pessoa tiver especificado uma outfile e especificado append inves de sobreescrever
}				t_cmd_table;

*/

/*
typedef struct s_pipex
{
	int		infile; X
	int		outfile; X
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	int		here_doc;
	pid_t	pid;
	int		cmd_nmbs; X
	int		pipe_nmbs; X
	int		*pipe;
	int		idx; X
	int		success;
}				t_pipex;

*/

/*
	Executar o pipex dentro do nosso programa.
	1- Criar uma função que abra o infile e outfile e coloque o fd deles em infile e outfile se existir. Se eles não
	//existirem passar stdin e stdout respectivamente para infile e outfile 0 e 1; Nós vamos substituir o check args.
	2- Vamos fazer uma função parecida com a init_data.

*/

void put_infile_fd(t_pipex *data, char *infile_path)
{
	if(data->infile_exists != 0)
	{
	data->infile = open(infile_path, O_RDONLY);
	if (data->infile < 0)
		msg_error("Invalid infile\n", 7);
	}
	else
	{
	data->infile = 0;	
	}
}

void put_outfile_fd(t_pipex *data, char *outfile_path)
{
	if(data->outfile_exists != 0)
	{
	data->outfile = open(outfile_path, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (data->outfile < 0)
	{
		close(data->infile);
		msg_error("Invalid Outfile\n", 8);
	}
	}
	else
	{
		data->outfile = 1;
	}
}

void init_data_executor(t_pipex *data, t_cmd_table *cmd_table, char *envp[])
{
	data->cmd_nmbs = cmd_table->n_of_cmds;
	data->pipe_nmbs = 2 * (data->cmd_nmbs - 1);
	data->idx = 0;
	data->success = 0;
	data->here_doc = 0; 
	data->pipe = (int *)malloc(sizeof(int) * data->pipe_nmbs);
	if (!data->pipe)
		close_io_exit(data, "Failed to malloc\n", 2);
	data->cmd_paths = ft_split(find_path(envp), ':');
	if (!data->cmd_paths)
		pipe_free(data, "failed to malloc\n", 3);
	init_pipes(data);
}

void executor_handler(char **envp)
{
	t_pipex data; 
	t_cmd_table cmd_table;
	char **comands_string;
	comands_string = malloc(sizeof(char*) * 3);
	comands_string[0] = ft_strdup("grep a");
	comands_string[1] = ft_strdup("grep b");
	comands_string[2] = ft_strdup("wc -l");
	cmd_table.comands_string = comands_string;
	data.infile_exists = 0;
	data.outfile_exists = 1;
	printf("Executor Handler \n");
	cmd_table.n_of_cmds = 3;
	put_infile_fd(&data, "./text1.txt");
	put_outfile_fd(&data, "./text2.txt");
	init_data_executor(&data, &cmd_table, envp);
	while (data.idx < data.cmd_nmbs)
	{
		child(data, cmd_table, envp);
		data.idx++;
	}
	close_pipes(&data);
	waitpid(-1, NULL, 0);
	parent_close(&data, "success", 0);
}

/*
	1- Eu criei as variaveis infile_exists e outfile_exists precisamos saber se eles existem precisamos setar eles para 1; 
*/