/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 00:11:04 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/20 00:59:16 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_list	*add_cmd(t_list *tct, int i)
{
	int size;

	size = cmd_size(tct);
	cmd_table->table[i] = ft_strdup((char *)tct->content);
	if (tct->next)
		tct = tct->next;
	while (size > 1)
	{
		cmd_table->table[i] = join_with_space(cmd_table->table[i], \
											(char *)tct->content);
		if (tct->next)
			tct = tct->next;
		size--;
	}
	return (tct);
}

int get_cmds(t_list *tct)
{
	int	i;

	i = 0;
	cmd_table->table = malloc(sizeof(char *) * (cmd_table->n_of_cmds + 1));
	while (tct)
	{
		if (is_special((char *)tct->content))
			tct = tct->next;
		else
		{
			tct = add_cmd(tct, i);
			i++;
		}
		tct = tct->next;
	}
	return (0);
}
