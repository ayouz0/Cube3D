/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:48 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/12 19:56:18 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	set_direction(t_player *player, char c, int row, int col)
{
	player->player_x = col * TILESIZE + TILESIZE / 2;
	player->player_y = row * TILESIZE + TILESIZE / 2;
	if (c == 'N')
		player->mv.player_angle = 3 * M_PI / 2;
	else if (c == 'S')
		player->mv.player_angle = M_PI / 2;
	else if (c == 'E')
		player->mv.player_angle = 0;
	else if (c == 'W')
		player->mv.player_angle = M_PI;
}

void	set_player_start_position(t_player *player, t_game *game)
{
	int		row;
	int		col;
	char	c;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			c = game->map[row][col];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_direction(player, c, row, col);
				game->map[row][col] = '0';
				return ;
			}
			col++;
		}
		row++;
	}
}

void	init_player(t_player *player, t_game *game)
{
	set_player_start_position(player, game);
	player->mv.turndir = 0;
	player->mv.walkdir = 0;
	player->mv.mov_speed = 3.5;
	player->mv.rotspeed = 3 * (M_PI / 180);
}
