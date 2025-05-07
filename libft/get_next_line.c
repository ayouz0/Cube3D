/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:55:51 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/06 13:54:02 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_found(char	*notbuffer)
{
	int	i;

	i = 0;
	while (notbuffer[i] != '\0')
	{
		if (notbuffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	free_buffer(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
}

char	*get_line_(int fd, char *remaining_str)
{
	ssize_t	bytes_read;
	char	*buffer;
	char	*tmp;

	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		tmp = remaining_str;
		remaining_str = ft_strjoin(remaining_str, buffer);
		if (remaining_str[0] == '\0')
			return (free_buffer(&buffer), NULL);
		free(tmp);
		if (ft_strchr(remaining_str, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		return (free_buffer(&buffer), NULL);
	free_buffer(&buffer);
	return (remaining_str);
}

char	*ft_fixer(char **line_buffer, char *remaining_str)
{
	size_t	i;

	i = 0;
	while ((*line_buffer)[i] != '\n' && (*line_buffer)[i] != '\0')
		i++;
	if ((*line_buffer)[i] == '\0')
		return (NULL);
	remaining_str = ft_substr(*line_buffer, i + 1, ft_strlen(*line_buffer) - i);
	(*line_buffer)[i + 1] = '\0';
	return (remaining_str);
}

char	*get_next_line(int fd)
{
	static char	*remaining_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
	{
		if (remaining_str)
			free_buffer(&remaining_str);
		return (NULL);
	}
	line = get_line_(fd, remaining_str);
	if (!line)
	{
		if (remaining_str)
			free_buffer(&remaining_str);
		return (NULL);
	}
	if (line[0] == '\0')
	{
		free_buffer(&line);
		return (NULL);
	}
	remaining_str = ft_fixer(&line, remaining_str);
	return (line);
}
