/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:03:36 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/16 20:29:22 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	has_wall_at(int x, int y, t_game *game)
{
	int	map_x = (int)(x / TILESIZE);
	int	map_y = (int)(y / TILESIZE);
	if (map_x < 0 || map_y < 0 ||
		map_x >= game->parse_data.width || map_y >= game->parse_data.height)
		return (1); // Out of bounds = wall

	char tile = game->map[map_y][map_x];
	if (tile == '1')
		return (1); // Wall
	if (game->ray.door.facing_up)
		map_y++;
	 if (map_y >= 0 && map_y < game->parse_data.height)
	 {
        tile = game->map[map_y][map_x];
        if (tile == 'D')
            return (2); // Door found
    }
	return (0);
}

int	iswall(float x, float y, char **map, t_game *game)
{
	int	map_x;
	int	map_y;
	int	map_y_d;

	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	map_y_d = map_y;
	if (game->ray.door.facing_up && game->ray.horz_hit_is_door)
	{
		write(1, "hello\n", 7);
		map_y_d = map_y + 1;
	}// i add one bcs i remove it before when it face up but this bcs its only one face
	if (map[map_y][map_x] == '1' || (map[map_y_d][map_x] == 'D' && game->door_state < 4))
		return (1);
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	map_y_d = map_y;
	if (game->ray.door.facing_up && game->ray.horz_hit_is_door)
	{
		write(1, "hello\n", 7);
		map_y_d = map_y + 1;
	}
	if (map[map_y][map_x] == '1' || (map[map_y_d][map_x] == 'D' && game->door_state < 4))
		return (1);
	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	map_y_d = map_y;
	if (game->ray.door.facing_up && game->ray.horz_hit_is_door)
	{
		write(1, "hello\n", 7);
		map_y_d = map_y + 1;
	}
	if (map[map_y][map_x] == '1' || (map[map_y_d][map_x] == 'D' && game->door_state < 4))
		return (1);
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	map_y_d = map_y;
	if (game->ray.door.facing_up && game->ray.horz_hit_is_door)
	{
		write(1, "hello\n", 7);
		map_y_d = map_y + 1;
	}
	if (map[map_y][map_x] == '1' || (map[map_y_d][map_x] == 'D' && game->door_state < 4))
		return (1);
	return (0);
}
