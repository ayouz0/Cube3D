/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:05:10 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/14 20:46:37 by hfhad            ###   ########.fr       */
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
	if (!iswall(new_x, new_y, game->map, game->keys.door_key))
	{
		game->player.player_x = new_x;
		game->player.player_y = new_y;
	}
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
	mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
	return (0);
}
