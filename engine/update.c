/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:05:10 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/11 11:21:17 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int iswall(float x, float y, char **map)
{
	int map_x, map_y;

	// Top-left
	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1') return 1;

	// Top-right
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1') return 1;

	// Bottom-left
	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1') return 1;

	// Bottom-right
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1') return 1;

	return 0;
}

int update(t_game *game)
{
	float	movestep;
	float	strafe_angle;
	float new_x;
	float new_y;
	t_ray ray;

	// Rotation
	if (game->keys.left)
		game->player.mv.player_angle -= game->player.mv.rotspeed;
	if (game->keys.right)
		game->player.mv.player_angle += game->player.mv.rotspeed;

	// Movement
	if (game->keys.w)
	{
		movestep = game->player.mv.mov_speed;
		new_x = game->player.player_x + cos(game->player.mv.player_angle) * movestep;
		new_y = game->player.player_y + sin(game->player.mv.player_angle) * movestep;
		if (!iswall(new_x, new_y, game->map))
		{
			game->player.player_x = new_x;
			game->player.player_y = new_y;
		}
	}
	if (game->keys.s)
	{
		movestep = game->player.mv.mov_speed;
		new_x = game->player.player_x + cos(game->player.mv.player_angle) * movestep * -1;
		new_y = game->player.player_y + sin(game->player.mv.player_angle) * movestep * -1;
		if (!iswall(new_x, new_y, game->map))
		{
			game->player.player_x = new_x;
			game->player.player_y = new_y;
		}
	}
	if (game->keys.a)
	{
		strafe_angle = game->player.mv.player_angle - M_PI / 2;
		new_x = game->player.player_x + cos(strafe_angle) * game->player.mv.mov_speed;
		new_y = game->player.player_y + sin(strafe_angle) * game->player.mv.mov_speed;
		if (!iswall(new_x, new_y, game->map))
		{
			game->player.player_x = new_x;
			game->player.player_y = new_y;
		}
	}
	if (game->keys.d)
	{
		strafe_angle = game->player.mv.player_angle + M_PI / 2;
		new_x = game->player.player_x + cos(strafe_angle) * game->player.mv.mov_speed;
		new_y = game->player.player_y + sin(strafe_angle) * game->player.mv.mov_speed;
		if (!iswall(new_x, new_y, game->map))
		{
			game->player.player_x = new_x;
			game->player.player_y = new_y;
		}
	}

	// Normalize angle to [0, 2π)
	game->player.mv.player_angle = normalize_angle(game->player.mv.player_angle);

	// printf("After update: angle=%f, x=%f, y=%f\n", game->player.mv.player_angle, game->player.player_x, game->player.player_y);
	clear_image(game);
	draw_sky(game);
	draw_floor(game);
	cast_all_rays(game, &ray);
	mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
	
	return (0);
}
