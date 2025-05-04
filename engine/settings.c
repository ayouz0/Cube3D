/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:04:27 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/04 17:14:15 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(1);
}

void    init_player(t_player *player, t_game *game)
{
	player->player_x = WINDOW_WIDTH / 2;
	player->player_y = WINDOW_HEIGHT / 2;
	player->mv.turndir = 0; // if 1 rotate to right -1 rotating to left 0 not rotating
	player->mv.walkdir = 0; // 0 not moving 1 moving forward -1 moving backwords
	player->mv.player_angle = 0; //50 * M_PI / 180;
	player->mv.mov_speed = 2.5;
	player->mv.rotspeed = 5 * (M_PI / 180);
	draw_player(game, (int)player->player_x, (int)player->player_y, 6, 0xFF0000);
	draw_line(game, player ,(int)player->player_x, (int)player->player_y, 32, 0xFF0000);
}
