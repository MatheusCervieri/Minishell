/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghosthologram <ghosthologram@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:07:41 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/19 16:36:18 by ghosthologr      ###   ########.fr       */
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
	cmd_table->infile = 0;
	cmd_table->outfile = 0;
	cmd_table->here_doc = 0;
	cmd_table->n_of_cmds = 0;
	cmd_table->n_of_pipes = 0;
	cmd_table->append = 0;
}

int	is_special(char *arg)
{
	return (*arg == '<' || *arg == '>' || *arg == '|');
}

void	handle_special(t_list *lst)
{
	if(ft_strncmp((char *)lst->content, "|", 2) == 0)
		cmd_table->n_of_pipes++;
	else
	{
		if(ft_strncmp((char *)lst->content, "<<", 2) == 0)
		{
			cmd_table->here_doc = 1;
			cmd_table->limiter = ft_strdup((char *)lst->next->content);
		}
		else if(ft_strncmp((char *)lst->content, ">>", 2) == 0)
		{
			cmd_table->append = 0;
			cmd_table->outfile = ft_strdup((char *)lst->next->content);
		}
		else if(ft_strncmp((char *)lst->content, "<", 2) == 0)
			cmd_table->infile = ft_strdup((char *)lst->next->content);
		else if(ft_strncmp((char *)lst->content, ">", 2) == 0)
			cmd_table->outfile = ft_strdup((char *)lst->next->content);
		lst = lst->next;
	}
}

int	parser(t_list *tmp)
{
	t_list	*ptr;
	t_list	*tmp;
	int		new_cmd;

	ptr = tmp;
	new_cmd = 0;
	while(ptr)
	{
		if (is_special((char*)ptr->content))
			handle_special(ptr);
		else
		{
			tmp = 
			while (ptr && ft_strncmp((char *)ptr->content, "|", 1))
			{

			}
		}
	}
}

int	parse_line(char *line)
{
	t_list	*tmp;

	if (!line)
		return (0);
	if (ft_strncmp(line, "exit", 5) == 0)
		return (1);
	init_global();
	tmp = lexer(line);
	if (!parser(tmp))
		//handle error
	return (0);
}