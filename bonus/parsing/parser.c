/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:46:53 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/13 12:24:42 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	space_neigh(char c)
{
	return ((c == '1') || (c == ' '));
}

int	check_top_bottom(char **map, int cols, int row)
{
	int	x;

	x = 0;
	while (x < cols)
	{
		if (!(map[row][x] == '1') && !(map[row][x] == ' '))
		{
			if (row == 0)
				return (printf("Error: Top border not closed\n"), 1);
			return (printf("Error: Bottom border not closed\n"), 1);
		}
		x++;
	}
	return (0);
}

int	check_side_borders(char **map, int rows, int cols)
{
	int	y;

	y = 0;
	while (y < rows)
	{
		if (!(map[y][0] == '1') && !(map[y][0] == ' '))
			return (printf("Error: Left border not closed\n"), 1);
		if (!(map[y][cols - 1] == '1') && !((map[y][cols - 1]) == ' '))
			return (printf("Error: Right border not closed\n"), 1);
		y++;
	}
	return (0);
}

void	increment_player_count(char c, long long *player_count)
{
	if ((c == 'N' || c == 'S' || \
		c == 'E' || c == 'W'))
		(*player_count)++;
}

int	parsing(int ac, char **av, t_game *game)
{
	if (ac != 2)
		return (printf("Error: usage: ./cub3d <filename>.cub\n"), 1);
	if (ft_strlen(av[1]) < 4 || ft_strncmp(av[1] + \
	ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		return (printf("Error: bad file extention\n"), 1);
	game->parse_data.c = -1;
	game->parse_data.f = -1;
	game->parse_data.no.ptr = 0x0;
	game->parse_data.so.ptr = 0x0;
	game->parse_data.we.ptr = 0x0;
	game->parse_data.ea.ptr = 0x0;
	if (load_cardinals_and_colors(game, av) != 0)
		return (1);
	if (load_map(game))
		return (1);
	if (validate_map(game->map, game->parse_data.height, \
	game->parse_data.width, game))
		return (free_2d(game->map), 1);
	return (0);
}
