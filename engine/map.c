/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:03:36 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/11 11:20:48 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

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

void draw_minisquare(t_game *game, int x, int y, int color, int size)
{
	int i, j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_in_img(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_sky(t_game *game)
{
	int x, y;
	int mini_size = TILESIZE / 16;
	int max_height = (ROWS * TILESIZE) / 2;

	y = 0;
	while (y < max_height)
	{
		x = 0;
		while (x < COLS * TILESIZE)
		{
			draw_minisquare(game, x, y, game->parse_data.c, mini_size);
			x += mini_size;
		}
		y += mini_size;
	}
}

void	draw_floor(t_game *game)
{
	int x, y;
	int mini_size = TILESIZE / 16;
	int start_y = (ROWS * TILESIZE) / 2;
	int end_y = ROWS * TILESIZE;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < COLS * TILESIZE)
		{
			draw_minisquare(game, x, y, game->parse_data.f, mini_size);
			x += mini_size;
		}
		y += mini_size;
	}
}

int	has_wall_at(int x, int y, t_game *game)
{
	int map_x = (int)(x / TILESIZE);
	int map_y = (int)(y / TILESIZE);

	if (map_x < 0 || map_x >= game->parse_data.width || map_y < 0 || map_y >= game->parse_data.height)
		return (1); // Treat out-of-bounds as wall

	return (game->map[map_y][map_x] == '1');
}

void clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_in_img(game, x, y, 0x000000); // black
			x++;
		}
		y++;
	}
}

