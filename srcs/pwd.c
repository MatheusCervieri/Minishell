/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:32:04 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/22 09:58:03 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void pwd_bi(void)
{
    char    *current_directory;
    
    current_directory = getcwd(NULL, 0);
    ft_putstr_fd(current_directory, 1);
    ft_putstr_fd("\n", 1);
}