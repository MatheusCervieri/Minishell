/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:07:41 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/19 23:10:03 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_table	*cmd_table;

t_list	*lexer(char *line)
{
	char	**split_line;
	t_list	*tmp;
	t_list	*rtn;

	split_line = ft_split(line, ' ');
	split_line = expander(split_line);
	rtn = ft_lstnew(*split_line);
	split_line++;
	while(*split_line)
	{
		tmp = ft_lstnew(*split_line);
		ft_lstadd_back(&rtn, tmp);
		split_line++;
	}
	return (rtn);
}

void init_global(void)
{
	cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	cmd_table->infile = ft_strdup("STDIN_FILENO");
	cmd_table->outfile = ft_strdup("STDOUT_FILENO");
	cmd_table->here_doc = 0;
	cmd_table->n_of_cmds = 0;
	cmd_table->n_of_pipes = 0;
	cmd_table->append = 0;
}

int	is_special(char *arg)
{
	return (*arg == '<' || *arg == '>' || *arg == '|');
}

void	handle_special(char *line, t_list **lst)
{
	if(ft_strncmp(line, "|", 2) == 0)
		cmd_table->n_of_pipes++;
	else
	{
		if(ft_strncmp(line, "<<", 2) == 0)
		{
			cmd_table->here_doc = 1;
			cmd_table->limiter = ft_strdup(((char *)lst[0]->next->content));
		}
		else if(ft_strncmp(line, ">>", 2) == 0)
		{
			cmd_table->append = 1;
			cmd_table->outfile = ft_strdup((char *)lst[0]->next->content);
		}
		else if(ft_strncmp(line, "<", 1) == 0)
		{
			free(cmd_table->infile);
			cmd_table->infile = ft_strdup((char *)lst[0]->next->content);
		}
		else if(ft_strncmp(line, ">", 1) == 0)
		{
			free(cmd_table->outfile);
			cmd_table->outfile = ft_strdup((char *)lst[0]->next->content);
		}
		lst[0] = lst[0]->next;
	}
}

int cmd_size(t_list *tmp_cmd_table)
{
	int	i;

	i = 0;
	while (tmp_cmd_table && !is_special((char *)tmp_cmd_table->content))
	{
		i++;
		tmp_cmd_table = tmp_cmd_table->next;
	}
	return (i);
}

int get_cmds(t_list *tmp_cmd_table)
{
	int	i;
	int size;

	i = 0;
	cmd_table->table = (char **)malloc(sizeof(char *) * (cmd_table->n_of_cmds + 1));
	while (tmp_cmd_table)
	{
		if (is_special((char *)tmp_cmd_table->content))
			tmp_cmd_table = tmp_cmd_table->next;
		else
		{
			size = cmd_size(tmp_cmd_table);
			cmd_table->table[i] = ft_strdup((char *)tmp_cmd_table->content);
			if (tmp_cmd_table->next)
				tmp_cmd_table = tmp_cmd_table->next;
			while (size > 1)
			{
				cmd_table->table[i] = join_with_space(cmd_table->table[i], (char *)tmp_cmd_table->content);
				if (tmp_cmd_table->next)
					tmp_cmd_table = tmp_cmd_table->next;
				size--;
			}
			i++;
		}
		tmp_cmd_table = tmp_cmd_table->next;
	}
	return 0;
}

int	parser(t_list *tmp_cmd_table)
{
	t_list	*ptr;

	ptr = tmp_cmd_table;
	while(ptr)
	{
		if (is_special((char *)ptr->content))
			handle_special((char *)ptr->content, &ptr);
		else
		{
			cmd_table->n_of_cmds++;
			while (ptr->next && is_special((char *)ptr->content))
				ptr = ptr->next;
		}
		ptr = ptr->next;
	}
	get_cmds(tmp_cmd_table);
	return (0);
}

int	parse_line(char *line)
{
	t_list	*tmp_cmd_table;

	if (!line)
		return (0);
	if (ft_strncmp(line, "exit", 5) == 0)
		return (1);
	init_global();
	tmp_cmd_table = lexer(line);
	parser(tmp_cmd_table);
	return (0);
}