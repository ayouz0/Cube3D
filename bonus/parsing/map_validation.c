/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:07:26 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/15 12:07:31 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_space_surrounded(t_map_ctx *ctx, int y, int x)
{
	char	**map;

	map = ctx->map;
	if ((y > 0 && !space_neigh(map[y - 1][x])) ||
		(y < ctx->rows - 1 && !space_neigh(map[y + 1][x])) ||
		(x > 0 && !space_neigh(map[y][x - 1])) ||
		(x < ctx->cols - 1 && !space_neigh(map[y][x + 1])))
		return (0);
	return (1);
}

int	check_map_cell(t_map_ctx *ctx, int y, int x, long long *player_count)
{
	char	**map;

	map = ctx->map;
	if (is_map_cell(map[y][x]))
	{
		increment_player_count(map[y][x], player_count);
		if ((y > 0 && map[y - 1][x] == ' ') ||
			(y < ctx->rows - 1 && map[y + 1][x] == ' ') ||
			(x > 0 && map[y][x - 1] == ' ') ||
			(x < ctx->cols - 1 && map[y][x + 1] == ' '))
		{
			printf("Error: Map leakage is not allowed\n");
			return (1);
		}
	}
	else if (map[y][x] == ' ' && !is_space_surrounded(ctx, y, x))
	{
		printf("Error: Space has an invalid neighbor\n");
		return (1);
	}
	return (0);
}

int	check_map_interior(char **map, int rows, int cols, long long *player_count)
{
	t_map_ctx	ctx;
	int			y;
	int			x;

	ctx.map = map;
	ctx.rows = rows;
	ctx.cols = cols;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (check_map_cell(&ctx, y, x, player_count))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

void	load_door(t_game *game, int door_count)
{
	int		y;
	int		x;
	char	**map;
	int		i;

	i = 0;
	y = 0;
	x = 0;
	map = game->map;
	game->doors = malloc(sizeof(t_door) * door_count);
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'D')
			{
				game->doors[i].x = x;
				game->doors[i].y = y;
				i++;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

int	check_invalid_characters(char **map, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->door_count = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if ((map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'D') && \
				(map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' && \
				map[i][j] != 'W'))
				return (printf \
				("Error: invalid character found while reading map:\n|%c|\n", \
				map[i][j]), 1);
			if (map[i][j] == 'D')
				game->door_count++;
			j++;
		}
		i++;
		j = 0;
	}
	if (game->door_count > 0)
		load_door(game, game->door_count);
	return (0);
}

int	validate_map(char **map, int rows, int cols, t_game *game)
{
	long long	player_count;

	player_count = 0;
	if (check_invalid_characters(map, game))
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
		return \
		(printf("Error: Multiple player spawns found (%lld)\n", \
		player_count), 1);
	return (0);
}
