/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_cardinals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/21 18:03:34 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**split_to_first_char(char *str, char sep)
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

static int	load_data(t_game *game, char *line)
{
	char	**split;
	void	*img;
	int		color;

	split = split_to_first_char(line, ' ');
	if (!split || !split[0] || !split[1])
		return (printf(INVALID_CONFG, line), free(line), free_2d(split), 1);
	if (trim_endl(split) == 0 && load_images(split, game, &img))
		return (1);
	if (ft_strncmp(split[0], "F", 2) == 0)
	{
		if (parse_rgb(split[1], &color))
			return (printf(FLOOR, split[1]), free_2d(split), 1);
		game->parse_data.f = color;
	}
	else if (ft_strncmp(split[0], "C", 2) == 0)
	{
		if (parse_rgb(split[1], &color))
			return (printf(CEILING, split[1]), free_2d(split), 1);
		game->parse_data.c = color;
	}
	if ((split[0][0] == 'N' || split[0][0] == 'S' || split[0][0] == 'W' || \
	split[0][0] == 'E') && !img)
		return (free_2d(split), printf(IMAGE_FAILURE), 1);
	return (free_2d(split), 0);
}

static int	all_have_been_loaded(t_game *game)
{
	return ((game->parse_data.no.ptr && game->parse_data.so.ptr \
		&& game->parse_data.ea.ptr && game->parse_data.we.ptr \
		&& game->parse_data.c != -1 && game->parse_data.f != -1));
}

static int	evaluate_line(char **line, t_game *game, int *counter)
{
	if (!(*line))
		return (close(game->parse_data.fd), printf(CARDINALS), free(*line), 1);
	if ((is_cardinal(*line) == 0 || is_color(*line) == 0))
	{
		if (load_data(game, *line) != 0)
			return (free(*line), close(game->parse_data.fd), 1);
		(*counter)++;
	}
	else
		return (printf(INVALID_LINE, *line), free(*line), 1);
	return (0);
}

int	load_cardinals_and_colors(t_game *game, char **av)
{
	char	*line;
	int		counter;

	(1) && (counter = 0, game->parse_data.fd = open(av[1], O_RDONLY));
	if (game->parse_data.fd == -1)
		return (printf(OPEN_FAILURE, av[1]), 1);
	line = get_next_line(game->parse_data.fd);
	if (!line)
		return (printf(CARDIN_COL), close(game->parse_data.fd), 1);
	while (1)
	{
		move_offset_to_map(&line, game->parse_data.fd);
		if (evaluate_line(&line, game, &counter) != 0)
			return (1);
		if (counter == 6)
		{
			if (all_have_been_loaded(game))
				break ;
			return (printf(DUPLICATE), free(line), \
			close(game->parse_data.fd), 1);
		}
		free(line);
		line = get_next_line(game->parse_data.fd);
	}
	return (free(line), 0);
}
