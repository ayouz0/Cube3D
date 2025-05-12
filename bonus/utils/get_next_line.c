/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:58:45 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/12 15:52:03 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_buf(char **buf, char *line)
{
	if (!line && buf && *buf)
	{
		free(*buf);
		*buf = NULL;
	}
}

char	*read_and_append(int fd, char **buf, char *reader)
{
	int		readed_bytes;
	char	*tmp;

	readed_bytes = read(fd, reader, BUFFER_SIZE);
	while (readed_bytes > 0)
	{
		if (!*buf)
			*buf = ft_strdup("");
		if (!*buf)
			return (NULL);
		reader[readed_bytes] = '\0';
		tmp = ft_strjoin(*buf, reader);
		free(*buf);
		*buf = tmp;
		if (!*buf)
			return (NULL);
		if (check_new_line(*buf) != -1)
			break ;
		readed_bytes = read(fd, reader, BUFFER_SIZE);
	}
	if (readed_bytes == -1)
		free_buf(buf, NULL);
	return (*buf);
}

char	*handle_existing_buf(char **buf)
{
	char	*line;

	if (*buf && check_new_line(*buf) != -1)
	{
		line = fill_fix_line(buf, check_new_line(*buf));
		return (line);
	}
	return (NULL);
}

char	*fix_line(char **buf)
{
	char	*line;

	if (*buf && check_new_line(*buf) != -1)
		line = fill_fix_line(buf, check_new_line(*buf));
	else if (*buf && **buf != '\0')
	{
		line = ft_strdup(*buf);
		free(*buf);
		*buf = NULL;
	}
	else
		line = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*reader;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	reader = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + (size_t)1));
	if (!reader)
		return (NULL);
	line = handle_existing_buf(&buf);
	if (line)
		return (free_buf(&reader, NULL), line);
	buf = read_and_append(fd, &buf, reader);
	if (!buf)
		return (free(reader), NULL);
	line = fix_line(&buf);
	free_buf(&reader, NULL);
	free_buf(&buf, line);
	return (line);
}
