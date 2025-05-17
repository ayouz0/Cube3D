/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:05:10 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/17 12:09:17 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	move_player(t_game *game, float angle)
{
	float	movestep;
	float	new_x;
	float	new_y;

	movestep = game->player.mv.mov_speed;
	new_x = game->player.player_x + cos(angle) * movestep;
	new_y = game->player.player_y + sin(angle) * movestep;
	if (!iswall(new_x, new_y, game->map, game))
	{
		game->player.player_x = new_x;
		game->player.player_y = new_y;
	}
}

// void	open_door(game)
// {
// 	int	door_state;

	
// }

void	door_button(t_game *game)
{
	// static long	last_update = 0;
	// static int	anim_frame = 0;
	// static int	direction = 1; // 1 = forward, -1 = backward
	// long		current_time;

	if (!game->has_button)
		return;
	draw_light_sprite(game, &game->door_button[game->door_state], 1 * 48, 2 * 48);
}

int	update(t_game *game)
{
	if (game->keys.left)
		game->player.mv.player_angle -= game->player.mv.rotspeed;
	if (game->keys.right)
		game->player.mv.player_angle += game->player.mv.rotspeed;
	if (game->keys.w)
		move_player(game, game->player.mv.player_angle);
	if (game->keys.s)
		move_player(game, game->player.mv.player_angle + M_PI);
	if (game->keys.a)
		move_player(game, game->player.mv.player_angle - M_PI_2);
	if (game->keys.d)
		move_player(game, game->player.mv.player_angle + M_PI_2);
	game->player.mv.player_angle = norma_angle(game->player.mv.player_angle);
	clear_image(game);
	draw_sky(game);
	draw_floor(game);
	cast_all_rays(game, &game->ray);
	if (game->light  % 2 == 0)
		animate_sprite(game);
	door_button(game);
	// open_door(game);
	game->door_tex = game->door_opening[2];
	mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
	return (0);
}
