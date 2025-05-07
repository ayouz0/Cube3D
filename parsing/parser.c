/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:46:53 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/07 11:15:46 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_color(char *line)
{
	if (!line)
		return(1);
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (0);
	return(1);
}

/*only one expression would be true for the string comparisons
makes "found" a bool*/
int	is_cardinal(char *line)
{
	int found;

	found = 0;
	if (!line)
		return(1);
	found += (!ft_strncmp(line, "NO ", 3)) + (!ft_strncmp(line, "SO ", 3)) \
	+ (!ft_strncmp(line, "EA ", 3)) + (!ft_strncmp(line, "WE ", 3));
	return (!found);
}

void	free_2d(char **array)
{
	int	i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	parse_rgb(char *str, int *out_color)
{
	char	**tmp;
	int		r;
	int		g;
	int		b;

	tmp = ft_split(str, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
		return (free_2d(tmp), 1);
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	free_2d(tmp);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	*out_color = (r << 16) | (g << 8) | b;
	return (0);
}

void	trim_endl(char **split)
{
	int i = 0;

	while (split[i])
	{
		int len = ft_strlen(split[i]);
		if (len > 0 && split[i][len - 1] == '\n')
			split[i][len - 1] = '\0';
		i++;
	}
}

int	load_data(t_game *game, char *line)
{
	char	**split;
	void	*img;
	int		color;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (printf("Error: Invalid config line: %s\n", line), free(line), 1);
	trim_endl(split);
	if (split[2] && split[2][0] != '\0')
		return (printf("Error: Invalid config line :\n%s", line));
	if (ft_strncmp(split[0], "NO", 3) == 0)
	{
		img = mlx_xpm_file_to_image(game->mlx, split[1], &game->parse_data.NO.w, &game->parse_data.NO.h);
		game->parse_data.NO.ptr = img;
	}
	else if (ft_strncmp(split[0], "SO", 3) == 0)
	{
		img = mlx_xpm_file_to_image(game->mlx, split[1], &game->parse_data.SO.w, &game->parse_data.SO.h);
		game->parse_data.SO.ptr = img;
	}
	else if (ft_strncmp(split[0], "WE", 3) == 0)
	{
		img = mlx_xpm_file_to_image(game->mlx, split[1], &game->parse_data.WE.w, &game->parse_data.WE.h);
		game->parse_data.WE.ptr = img;
	}
	else if (ft_strncmp(split[0], "EA", 3) == 0)
	{
		img = mlx_xpm_file_to_image(game->mlx, split[1], &game->parse_data.EA.w, &game->parse_data.EA.h);
		game->parse_data.EA.ptr = img;
	}
	else if (ft_strncmp(split[0], "F", 2) == 0)
	{
		if (parse_rgb(split[1], &color))
			return (free_2d(split), printf("Error: Invalid floor color: %s\n", split[1]), 1);
		game->parse_data.f = color;
	}
	else if (ft_strncmp(split[0], "C", 2) == 0)
	{
		if (parse_rgb(split[1], &color))
			return (free_2d(split), printf("Error: Invalid ceiling color: %s\n", split[1]), 1);
		game->parse_data.c = color;
	}
	if ((split[0][0] == 'N' || split[0][0] == 'S' || split[0][0] == 'W' || split[0][0] == 'E') && !img)
		return (free_2d(split), printf("Error: failed to load an image\n"), 1);
	free_2d(split);
	return (0);
}


int	load_cardinals_and_colors(t_game *game, char **av)
{
	char	*line;
	int		counter;

	counter = 0;
	game->parse_data.fd = open(av[1], O_RDONLY);
	if (game->parse_data.fd == -1)
		return (printf("Error: failed to open the file \"%s\"\n", av[1]), 1);
	line = get_next_line(game->parse_data.fd);
	if (!line)
		return (printf("Error: files mustn't be empty\n"), 1);
	while (1)
	{
		while (line && line[0] == '\n')
		{
			free(line);
			line = get_next_line(game->parse_data.fd);
		}
		if (!line)
			return (printf("Error: couldn't load all cardinals/colors\n"), 1);
		if (is_cardinal(line) == 0 || is_color(line) == 0)
		{
			if (load_data(game, line) != 0)
				return (1);
			counter++;
		}
		else
			return (printf("Error: invalid line while parsing cardinals/colors:\n%s\n", line), free(line), 1);
		if (counter == 6)
		{
			free(line);
			break;
		}
		line = get_next_line(game->parse_data.fd);
	}
	return (0);
}

static void	free_map(char **map, int rows)
{
	int i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}

static int	count_map_lines_and_maxlen(int fd, int *max_len, char ***lines)
{
	char	*line;
	int		count;
	int		len;
	char	**tmp;
	int		i;

	i = 0;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len-- - 1] = '\0';
		if (len > *max_len)
			*max_len = len;
		tmp = malloc(sizeof(char *) * (count + 2));
		if (!tmp)
			return (free(line), free_map(*lines, count), -1);
		i = 0; 
		while (i < count)
		{
			tmp[i] = (*lines)[i];
			i++;
		}
		tmp[count] = line;
		tmp[count + 1] = NULL;
		free(*lines);
		*lines = tmp;
		line = get_next_line(fd);
		count++;
	}
	return (count);
}

static char **pad_map_lines(char **lines, int count, int max_len)
{
    char **map;
    int i;
    int j;

	map = malloc(sizeof(char *) * (count + 1));
	i = 0;
    if (!map)
        return (NULL);
    while (i < count)
    {
        map[i] = malloc(max_len + 1);
        if (!map[i])
        {
        	j = 0;
            while (j < i)
            {
                free(map[j]);
                j++;
            }
            free(map);
            return NULL;
		}
        j = 0;
        while (lines[i][j])
        {
            map[i][j] = lines[i][j];
            j++;
        }
        while (j < max_len)
        {
            map[i][j] = ' ';
            j++;
        }
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
	num_lines = count_map_lines_and_maxlen(game->parse_data.fd, &max_len, &lines);
	if (num_lines <= 0)
		return (printf("Error: map couldn't be read or is empty\n"), 1);
	game->map = pad_map_lines(lines, num_lines, max_len);
	for (int i = 0; game->map[i]; i++)
		printf("|%s|\n", game->map[i]);
	free_map(lines, num_lines);
	if (!game->map)
		return (printf("Error: failed to allocate map memory\n"), 1);
	// if (validate_map(game, game->map, num_lines, max_len))
	// 	return (printf("Error: %s\n", game->error_msg), free_map(game->map, num_lines), 1);

	return (0);
}
int	parsing(int ac, char **av, t_game *game)
{
	(void)game;
	if (ac != 2)
		return (printf("Error: usage: ./cub3d <filename>.cub\n"), 1);
	if (ft_strlen(av[1]) < 4 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		return (printf("Error: bad file extention\n"), 1);
	if (load_cardinals_and_colors(game, av) != 0)
		return (1);
	if (load_map(game))
		return (1);
	return(0);
}
