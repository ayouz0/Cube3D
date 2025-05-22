/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:49:07 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/22 10:18:17 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	move_offset_to_map(char **line, int fd)
{
	while (*line && (*line)[0] == '\n')
	{
		free(*line);
		*line = get_next_line(fd);
	}
}

static int	count_map_lines_and_maxlen(int fd, int *max_len, char ***lines)
{
	char	*line;
	int		count;
	int		len;
	char	**tmp;
	int		i;

	(1) && (i = 0, count = 0, line = get_next_line(fd));
	move_offset_to_map(&line, fd);
	while (line)
	{
		len = ft_strlen(line);
		(line[len - 1] == '\n') && (line[len-- - 1] = '\0');
		(len > *max_len) && (*max_len = len);
		tmp = malloc(sizeof(char *) * (count + 2));
		if (!tmp)
			return (free(line), free_map(*lines, count), -1);
		i = -1;
		while (++i < count)
			tmp[i] = (*lines)[i];
		(1) && (tmp[count] = line, tmp[count + 1] = NULL);
		free(*lines);
		(1) && (*lines = tmp, line = get_next_line(fd));
		count++;
	}
	return (count);
}

void	pad_up(char ***map, int max_len, int *i, int *j)
{
	while (*j < max_len)
	{
		(*map)[*i][*j] = ' ';
		(*j)++;
	}
}

static char	**pad_map_lines(char **lines, int count, int max_len)
{
	char	**map;
	int		i;
	int		j;

	map = malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (!map)
		return (NULL);
	while (i < count)
	{
		map[i] = malloc(max_len + 1);
		if (!map[i])
			return (free_map(map, i), NULL);
		j = 0;
		while (lines[i][j])
		{
			map[i][j] = lines[i][j];
			j++;
		}
		pad_up(&map, max_len, &i, &j);
		map[i][j] = '\0';
		i++;
	}
	map[count] = NULL;
	return (map);
}

int	load_map(t_game *game)
{
	char	**lines;
	int		max_len;
	int		num_lines;

	max_len = 0;
	lines = NULL;
	num_lines = count_map_lines_and_maxlen(game->parse_data.fd, \
	&max_len, &lines);
	if (num_lines <= 0)
	{
		if (num_lines == 0)
			printf("Error: map couldn't be read or is empty\n");
		return (1);
	}
	game->map = pad_map_lines(lines, num_lines, max_len);
	free_map(lines, num_lines);
	if (!game->map)
		return (printf("Error: failed to allocate map memory\n"), \
		free_parse_data(game), 1);
	game->parse_data.height = num_lines;
	game->parse_data.width = max_len;
	return (0);
}
