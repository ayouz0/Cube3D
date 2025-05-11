/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:05:10 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/11 12:08:39 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int update(t_game *game)
{
	float	movestep;
	float	strafe_angle;
	float new_x;
	float new_y;
	t_ray ray;

	if (game->keys.left)
		game->player.mv.player_angle -= game->player.mv.rotspeed;
	if (game->keys.right)
		game->player.mv.player_angle += game->player.mv.rotspeed;
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
	game->player.mv.player_angle = normalize_angle(game->player.mv.player_angle);
	clear_image(game);
	draw_sky(game);
	draw_floor(game);
	cast_all_rays(game, &ray);
	mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
	return (0);
}
