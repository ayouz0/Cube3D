/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_cardinals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/12 14:08:15 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**split_to_first_char(char *str, char sep)
{
	char	*second_string;
	char	**new;

	second_string = ft_strchr(str, sep);
	if (!second_string)
		return ((char **)str);
	second_string[0] = '\0';
	second_string++;
	new = malloc(sizeof(char *) * 3);
	new[0] = ft_strdup(str);
	new[1] = ft_strdup(second_string);
	new[2] = 0x0;
	return (new);
}

void	load_image_and_address(void	**img, t_game *game, \
char *filename, t_cardinals *cardinal)
{
	*img = mlx_xpm_file_to_image(game->mlx, filename, &cardinal->w, \
	&cardinal->h);
	cardinal->ptr = *img;
	if (*img)
		cardinal->addr = mlx_get_data_addr(cardinal->ptr, \
		&cardinal->bits_per_pixel, &cardinal->line_length, \
		&cardinal->endian);
}

void	load_images(char **split, t_game *game, void **img)
{
	if (ft_strncmp(split[0], "NO", 3) == 0)
		load_image_and_address(img, game, split[1], &game->parse_data.no);
	else if (ft_strncmp(split[0], "SO", 3) == 0)
		load_image_and_address(img, game, split[1], &game->parse_data.so);
	else if (ft_strncmp(split[0], "WE", 3) == 0)
		load_image_and_address(img, game, split[1], &game->parse_data.we);
	else if (ft_strncmp(split[0], "EA", 3) == 0)
		load_image_and_address(img, game, split[1], &game->parse_data.ea);
}

int	load_data(t_game *game, char *line)
{
	char	**split;
	void	*img;
	int		color;

	split = split_to_first_char(line, ' ');
	if (!split || !split[0] || !split[1])
		return (printf("Error: Invalid config line: %s\n", line), \
		free(line), free_2d(split), 1);
	(trim_endl(split), load_images(split, game, &img));
	if (ft_strncmp(split[0], "F", 2) == 0)
	{
		if (parse_rgb(split[1], &color))
			return (printf("Error: Invalid floor color: %s\n", \
			split[1]), free_2d(split), 1);
		game->parse_data.f = color;
	}
	else if (ft_strncmp(split[0], "C", 2) == 0)
	{
		if (parse_rgb(split[1], &color))
			return (printf("Error: Invalid ceiling color: %s\n", split[1]), \
			free_2d(split), 1);
		game->parse_data.c = color;
	}
	if ((split[0][0] == 'N' || split[0][0] == 'S' || split[0][0] == 'W' || \
	split[0][0] == 'E') && !img)
		return (free_2d(split), printf("Error: failed to load an image\n"), 1);
	return (free_2d(split), 0);
}

int	all_have_been_loaded(t_game *game)
{
	return ((game->parse_data.no.ptr && game->parse_data.so.ptr \
		&& game->parse_data.ea.ptr && game->parse_data.we.ptr \
		&& game->parse_data.c != -1 && game->parse_data.f != -1));
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
		return (printf("Error: couldn't load all cardinals/colors\n"), close(game->parse_data.fd), 1);
	while (1)
	{
		while (line && line[0] == '\n')
		{
			free(line);
			line = get_next_line(game->parse_data.fd);
		}
		if (!line)
			return (close(game->parse_data.fd), printf("Error: couldn't load all cardinals/colors\n"), free(line), 1);
		if ((is_cardinal(line) == 0 || is_color(line) == 0))
		{
			if (load_data(game, line) != 0)
				return (free(line), close(game->parse_data.fd), 1);
			counter++;
		}
		else
			return (printf("Error: invalid line while parsing cardinals/colors:\n%s", line), free(line), 1);
		if (counter == 6)
		{
			if (all_have_been_loaded(game))
				break;
			return (printf("Error: found duplicate config info\n"), free(line), close(game->parse_data.fd), 1);
		}
		free(line);
		line = get_next_line(game->parse_data.fd);
	}
	return (free(line), 0);
}
