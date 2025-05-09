/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:48 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/08 20:17:08 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void draw_player(t_game *game, int x, int y, int radius, int color)
{
	int i;
	int	j;
	int	dx;
	int	dy;

	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			dx = i;
			dy = j;
			if (dx * dx + dy * dy <= radius * radius)
				put_pixel_in_img(game, x + dx, y + dy, color);
			j++;
		}
		i++;
	}
}

void draw_line(t_game *game, t_player *player, int x, int y, float line_length, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int e2;

	player->mv.dir_y = sin(player->mv.player_angle);
	player->mv.dir_x = cos(player->mv.player_angle);
	player->mv.end_x = (int)(x + player->mv.dir_x * line_length);
	player->mv.end_y = (int)(y + player->mv.dir_y * line_length);
	dx = abs(player->mv.end_x - x);
	dy = abs(player->mv.end_y - y);
	sx = x < player->mv.end_x ? 1 : -1;
	sy = y < player->mv.end_y ? 1 : -1;
	player->mv.err = dx - dy;
	while (1)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			put_pixel_in_img(game, x, y, color);
		}
		if (x == player->mv.end_x && y == player->mv.end_y)
			break;
		e2 = player->mv.err * 2;
		if (e2 > -dy)
		{
			player->mv.err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			player->mv.err += dx;
			y += sy;
		}
	}
}
