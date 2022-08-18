/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:22:23 by mvieira-          #+#    #+#             */
/*   Updated: 2022/08/18 20:48:26 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	free_memory(char **s1, char **s2, char **s3)
{
	if (s1)
	{
		if (*s1)
			free(*s1);
		*s1 = NULL;
	}
	if (s2)
	{
		if (*s2)
			free(*s2);
		*s2 = NULL;
	}
	if (s3)
	{
		if (*s3)
			free(*s3);
		*s3 = NULL;
	}
}

char	*save_chars_after_nl(char *line_text)
{
	char			*saved;
	int				nl_position;
	unsigned int	i;

	nl_position = is_there_nl(line_text);
	if (!(nl_position >= 0))
		return (NULL);
	saved = malloc((ft_strlen(line_text) - nl_position + 1) * sizeof(char));
	if (!saved)
		return (NULL);
	i = 0;
	while (i < ft_strlen(line_text) - nl_position)
	{
		saved[i] = line_text[nl_position + 1 + i];
		i++;
	}
	saved[i] = '\0';
	return (saved);
}

char	*get_line(char *line_text)
{
	char			*line;
	unsigned int	i;

	if (!line_text)
		return (NULL);
	i = 0;
	if (is_there_nl(line_text) != -1)
	{
		line = malloc(is_there_nl(line_text) + 2 * sizeof(char));
		if (!line)
			return (NULL);
		while (i <= (unsigned int)is_there_nl(line_text))
		{
			line[i] = line_text[i];
			i++;
		}
		line[i] = '\0';
	}
	else
	{
		return (line_text);
	}
	free(line_text);
	return (line);
}

static char	*make_line(char **saved, char **buffer, char **l_text, int a_read)
{
	if (a_read == 0)
	{
		free_memory(saved, buffer, NULL);
		if (*l_text && **l_text)
			return (*l_text);
		free_memory(l_text, NULL, NULL);
		return (NULL);
	}
	free_memory(saved, buffer, NULL);
	*saved = save_chars_after_nl(*l_text);
	*l_text = get_line(*l_text);
	return (*l_text);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line_text;
	char		*buffer;
	int			actually_read;

	if (!saved)
		saved = ft_strdup("");
	line_text = ft_strdup(saved);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	actually_read = BUFFER_SIZE;
	while (BUFFER_SIZE == actually_read && !(is_there_nl(line_text) >= 0))
	{
		actually_read = read(fd, buffer, BUFFER_SIZE);
		if (actually_read < 0)
		{
			free_memory(&saved, &line_text, &buffer);
			return (NULL);
		}
		buffer[actually_read] = '\0';
		line_text = ft_strjoin_free(line_text, buffer);
	}
	return (make_line(&saved, &buffer, &line_text, actually_read));
}
