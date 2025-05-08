/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:04:27 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/07 18:27:43 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(1);
}

void	set_player_start_position(t_player *player, t_game *game)
{
	int row = 0, col;
	char c;

	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			c = game->map[row][col];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player->player_x = col * TILESIZE + TILESIZE / 2;
				player->player_y = row * TILESIZE + TILESIZE / 2;

				if (c == 'N')
					player->mv.player_angle = M_PI / 2;
				else if (c == 'S')
					player->mv.player_angle = 3 * M_PI / 2;
				else if (c == 'E')
					player->mv.player_angle = 0;
				else if (c == 'W')
					player->mv.player_angle = M_PI;

				// Replace starting point with walkable tile
				game->map[row][col] = '0';
				return;
			}
			col++;
		}
		row++;
	}
}

void    init_player(t_player *player, t_game *game)
{
	set_player_start_position(player, game);
	player->mv.turndir = 0;
	player->mv.walkdir = 0;
	player->mv.mov_speed = 8.5;
	player->mv.rotspeed = 5 * (M_PI / 180);
	draw_player(game, (int)player->player_x, (int)player->player_y, 6, 0xFF0000);
	draw_line(game, player ,(int)player->player_x, (int)player->player_y, 32, 0xFF0000);
}
