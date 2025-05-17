/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:03:36 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/17 20:58:37 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	has_wall_at(int x, int y, t_game *game)
{
	int		map_x;
	int		map_y;
	char	tile;

	map_x = (int)(x / TILESIZE);
	map_y = (int)(y / TILESIZE);
	if (map_x < 0 || map_y < 0 || \
		map_x >= game->parse_data.width || map_y >= game->parse_data.height)
		return (1);
	tile = game->map[map_y][map_x];
	if (tile == '1')
		return (1);
	if (game->ray.door.facing_up)
		map_y++;
	if (map_y >= 0 && map_y < game->parse_data.height)
	{
		tile = game->map[map_y][map_x];
		if (tile == 'D')
			return (2);
	}
	return (0);
}

int	iswall(float x, float y, char **map, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || \
		(map[map_y][map_x] == 'D' && game->door_state < 4))
		return (1);
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || \
		(map[map_y][map_x] == 'D' && game->door_state < 4))
		return (1);
	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || \
		(map[map_y][map_x] == 'D' && game->door_state < 4))
		return (1);
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || \
		(map[map_y][map_x] == 'D' && game->door_state < 4))
		return (1);
	return (0);
}
