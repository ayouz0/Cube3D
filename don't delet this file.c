/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   don't delet this file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:31:10 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/15 23:39:13 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

unsigned int	shade_color(unsigned int color, float distance)
{
	float			shade_factor;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	// !ahm ahm
	//? Light intensity = 1 / (1 + k * distance) Where k is a constant
	shade_factor = 1.0f / (1.0f + distance * 0.01f);
	r = ((color >> 16) & 0xFF) * shade_factor;
	g = ((color >> 8) & 0xFF) * shade_factor;
	b = (color & 0xFF) * shade_factor;
	return ((r << 16) | (g << 8) | b);
}

void draw_square(t_game *game, int x, int y, int color)
{
	int i, j;

	i = 0;
	while (i < TILESIZE)
	{
		j = 0;
		while (j < TILESIZE)
		{
			put_pixel_in_img(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_map(t_game *game, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (y < ROWS)
	{
		x = 0;
		while (x < COLS)
		{
			if (map[y][x] == '1')
				draw_square(game, x * TILESIZE, y * TILESIZE, 0x404040);
			else if (map[y][x] == '0' || map[y][x] == 'N')
				draw_square(game, x * TILESIZE, y * TILESIZE, 0xFFFFFF);
			else
				draw_square(game, x * TILESIZE, y * TILESIZE, 0x000000);
			x++;
		}
		y++;
	}
}


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

void draw_square(t_game *game, int x, int y, int color)
{
	int i, j;

	i = 0;
	while (i < TILESIZE)
	{
		j = 0;
		while (j < TILESIZE)
		{
			put_pixel_in_img(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void draw_line(t_game *game, t_player *player, int x, int y, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	e2;

	player->mv.dir_y = sin(player->mv.player_angle);
	player->mv.dir_x = cos(player->mv.player_angle);
	player->mv.end_x = (int)(x + player->mv.dir_x * LINE_LENGHT);
	player->mv.end_y = (int)(y + player->mv.dir_y * LINE_LENGHT);
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

// render_map(game, game->map);
// draw_player(game, (int)game->player.player_x, (int)game->player.player_y, 6, 0xFF0000);
// draw_line(game, &game->player, (int)game->player.player_x, (int)game->player.player_y, middle_ray_dist, 0xFF0000);