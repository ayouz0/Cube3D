/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:46:53 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/11 10:33:48 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_valid_space_neighbor(char c)
{
	return (IS_WALL(c) || IS_SPACE(c));
}
static int	check_top_bottom(char **map, int cols, int row)
{
	int	x;

	x = 0;
	while (x < cols)
	{
		if (!IS_WALL(map[row][x]) && !IS_SPACE(map[row][x]))
		{
			if (row == 0)
				return (printf("Error: Top border not closed\n"), 1);
			else
				return (printf("Error: Bottom border not closed\n"), 1);
		}
		x++;
	}
	return (0);
}

static int	check_side_borders(char **map, int rows, int cols)
{
	int	y;

	y = 0;
	while (y < rows)
	{
		if (!IS_WALL(map[y][0]) && !IS_SPACE(map[y][0]))
			return (printf("Error: Left border not closed\n"), 1);
		if (!IS_WALL(map[y][cols - 1]) && !IS_SPACE(map[y][cols - 1]))
			return (printf("Error: Right border not closed\n"), 1);
		y++;
	}
	return (0);
}

static int	check_walkable_tile(char **map, int y, int x, int rows, int cols)
{
	if ((y > 0 && map[y - 1][x] == ' ') ||
		(y < rows - 1 && map[y + 1][x] == ' ') ||
		(x > 0 && map[y][x - 1] == ' ') ||
		(x < cols - 1 && map[y][x + 1] == ' '))
		return (printf("Error: Map leakage is not allowed\n"), 1);
	return (0);
}

static int	check_space_tile(char **map, int y, int x, int rows, int cols)
{
	if ((y > 0 && !is_valid_space_neighbor(map[y - 1][x])) ||
		(y < rows - 1 && !is_valid_space_neighbor(map[y + 1][x])) ||
		(x > 0 && !is_valid_space_neighbor(map[y][x - 1])) ||
		(x < cols - 1 && !is_valid_space_neighbor(map[y][x + 1])))
		return (printf("Error: Space has an invalid neighbor\n"), 1);
	return (0);
}

static int	check_map_interior(char **map, int rows, int cols, long long *player_count)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (IS_WALKABLE(map[y][x]))
			{
				if (IS_PLAYER(map[y][x]))
					(*player_count)++;
				if (check_walkable_tile(map, y, x, rows, cols))
					return (1);
			}
			else if (map[y][x] == ' ')
			{
				if (check_space_tile(map, y, x, rows, cols))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_invalid_characters(char **map)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if ((map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0') && \
				(map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' && \
				map[i][j] != 'W'))
				return(printf("Error: invalid character found while reading map:\n|%c|\n", map[i][j]), 1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	validate_map(char **map, int rows, int cols)
{
	long long	player_count;

	player_count = 0;
	if (check_invalid_characters(map))
		return (1);
	if (check_top_bottom(map, cols, 0))
		return (1);
	if (check_top_bottom(map, cols, rows - 1))
		return (1);
	if (check_side_borders(map, rows, cols))
		return (1);
	if (check_map_interior(map, rows, cols, &player_count))
		return (1);
	if (player_count == 0)
		return (printf("Error: No player spawn found\n"), 1);
	if (player_count != 1)
		return (printf("Error: Multiple player spawns found (%lld)\n", player_count), 1);
	return (0);
}

int	parsing(int ac, char **av, t_game *game)
{
	if (ac != 2)
		return (printf("Error: usage: ./cub3d <filename>.cub\n"), 1);
	if (ft_strlen(av[1]) < 4 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		return (printf("Error: bad file extention\n"), 1);
	game->parse_data.c = -1;
	game->parse_data.f = -1;
	game->parse_data.NO.ptr = 0x0;
	game->parse_data.SO.ptr = 0x0;
	game->parse_data.WE.ptr = 0x0;
	game->parse_data.EA.ptr = 0x0;
	if (load_cardinals_and_colors(game, av) != 0)
		return (free_parse_data(game), 1);
	if (load_map(game))
		return (1);
	if (validate_map(game->map, game->parse_data.height, game->parse_data.width))
		return (free_2d(game->map), 1);
	return(0);
}
