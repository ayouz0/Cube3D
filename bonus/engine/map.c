/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:03:36 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/14 20:45:39 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	has_wall_at(int x, int y, t_game *game)
{
	int	map_x = (int)(x / TILESIZE);
	int	map_y = (int)(y / TILESIZE);
	int	i = 0;
	if (map_x < 0 || map_y < 0 ||
		map_x >= game->parse_data.width || map_y >= game->parse_data.height)
		return (1); // Out of bounds = wall

	char tile = game->map[map_y][map_x];
	if (tile == '1')
		return (1); // Wall
	else if (tile == 'D')
	{
		// Check door openness
		while (i < game->door_count)
		{
			if (game->doors[i].x == map_x && game->doors[i].y == map_y)
			{
					return (2); // Still acts as door
			}
			i++;
		}
	}
	return (0);
}

int	iswall(float x, float y, char **map, int door_key)
{
	int	map_x;
	int	map_y;

	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || (map[map_y][map_x] == 'D' && door_key == 0))
		return (1);
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || (map[map_y][map_x] == 'D' && door_key == 0))
		return (1);
	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || (map[map_y][map_x] == 'D' && door_key == 0))
		return (1);
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || (map[map_y][map_x] == 'D' && door_key == 0))
		return (1);
	return (0);
}
