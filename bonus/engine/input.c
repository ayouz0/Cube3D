/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:04:09 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/17 20:53:37 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	player_inside_door(t_game *game)
{
	int		player_map_x;
	int		player_map_y;
	int		y;
	int		x;
	int		check_y;
	int		check_x;
	float	door_center_x;
	float	door_center_y;
	float	distance;

	y = -1;
	player_map_x = (int)(game->player.player_x / TILESIZE);
	player_map_y = (int)(game->player.player_y / TILESIZE);
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			check_y = player_map_y + y;
			check_x = player_map_x + x;
			if (check_y < 0 || check_x < 0 || !game->map[check_y] || !game->map[check_y][check_x])
				continue ;
			if (game->map[check_y][check_x] == 'D')
			{
				door_center_x = (check_x * TILESIZE) + (TILESIZE / 2);
				door_center_y = (check_y * TILESIZE) + (TILESIZE / 2);
				distance = sqrt(pow(game->player.player_x - door_center_x, 2) + \
								pow(game->player.player_y - door_center_y, 2));
				if (distance < TILESIZE * 0.7)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	door_key(int key, t_game *game)
{
	if (key == 49 && game->has_button)
	{
		if (game->door_state <= 5 && \
			game->door_state > 0 && game->door_open == 1)
		{
			if (!player_inside_door(game))
			{
				game->door_state--;
				if (game->door_state == 0)
					game->door_open = 0;
			}
			else
				printf("you can't close the"\
					"door while your inside it (⌐■_■)\n");
		}
		else if (game->door_open == 0)
		{
			game->door_state++;
			if (game->door_state == 5)
				game->door_open = 1;
		}
	}
}

int	key_press(int key, t_game *game)
{
	if (key == 53)
		close_window(game);
	door_key(key, game);
	if (key == 11)
		game->has_button = !game->has_button;
	else if (key == 3)
		game->light++;
	else if (key == 13)
		game->keys.w = 1;
	else if (key == 1)
		game->keys.s = 1;
	else if (key == 0)
		game->keys.a = 1;
	else if (key == 2)
		game->keys.d = 1;
	else if (key == 123)
		game->keys.left = 1;
	else if (key == 124)
		game->keys.right = 1;
	else if (key == 257 && game->is_healed == 1)
		game->player.mv.mov_speed = 8;
	else if (key == 46)
		game->show_minimap = !game->show_minimap;
	game->minimap.cell_size += (key == 126) + (- (key == 125));
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 13)
		game->keys.w = 0;
	else if (key == 1)
		game->keys.s = 0;
	else if (key == 0)
		game->keys.a = 0;
	else if (key == 2)
		game->keys.d = 0;
	else if (key == 123)
		game->keys.left = 0;
	else if (key == 124)
		game->keys.right = 0;
	else if (key == 257)
		game->player.mv.mov_speed = 3.5;
	return (0);
}
