/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:05:10 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/04 17:15:15 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

char *map[] = {
	"1111111111111111",
	"1000000000000001",
	"1000111000000001",
	"1000001000000001",
	"1000001000111001",
	"1000001000001001",
	"1000000000001001",
	"1000000000000001",
	"1111111111111111",
	NULL
};

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int update(t_game *game)
{
	float	movestep;
	float	strafe_angle;
	// t_ray	ray;
	// Rotation
	if (game->keys.left)
		game->player.mv.player_angle -= game->player.mv.rotspeed;
	if (game->keys.right)
		game->player.mv.player_angle += game->player.mv.rotspeed;

	// Movement
	if (game->keys.w)
	{
		movestep = game->player.mv.mov_speed;
		game->player.player_x += cos(game->player.mv.player_angle) * movestep;
		game->player.player_y += sin(game->player.mv.player_angle) * movestep;
	}
	if (game->keys.s)
	{
		movestep = game->player.mv.mov_speed;
		game->player.player_x += cos(game->player.mv.player_angle) * movestep * -1;
		game->player.player_y += sin(game->player.mv.player_angle) * movestep * -1;
	}
	if (game->keys.a)
	{
		strafe_angle = game->player.mv.player_angle - M_PI / 2;
		game->player.player_x += cos(strafe_angle) * game->player.mv.mov_speed;
		game->player.player_y += sin(strafe_angle) * game->player.mv.mov_speed;
	}
	if (game->keys.d)
	{
		strafe_angle = game->player.mv.player_angle + M_PI / 2;
		game->player.player_x += cos(strafe_angle) * game->player.mv.mov_speed;
		game->player.player_y += sin(strafe_angle) * game->player.mv.mov_speed;
	}

	// Normalize angle to [0, 2π)
	game->player.mv.player_angle = normalize_angle(game->player.mv.player_angle);

	// printf("After update: angle=%f, x=%f, y=%f\n", game->player.mv.player_angle, game->player.player_x, game->player.player_y);
	clear_image(game);
	// cast_all_rays(game, &ray);
	render_map(game, map);
	draw_player(game, (int)game->player.player_x, (int)game->player.player_y, 6, 0xFF0000);
	draw_line(game, &game->player, (int)game->player.player_x, (int)game->player.player_y, 42, 0xFF0000);
	mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
	return (0);
}
