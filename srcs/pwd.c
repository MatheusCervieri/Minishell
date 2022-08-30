/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:32:04 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/29 21:46:22 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void pwd_bi(int fd[2])
{
    char    *current_directory;
    
    current_directory = getcwd(NULL, 0);
    ft_putstr_fd(current_directory, 1);
    ft_putstr_fd("\n", 1);
    convert_list_to_fd_fds(fd);
}