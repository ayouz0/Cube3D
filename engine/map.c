/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:03:36 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/04 17:05:27 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void draw_square(t_game *game, int x, int y, int color)
{
	int i, j;

	i = 0;
	while (i < TILESIZE- 1)
	{
		j = 0;
		while (j < TILESIZE - 1)
		{
			put_pixel_in_img(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

int	has_wall_at(int x, int y, char **map)
{
	return (map[(int)(y / TILESIZE)][(int)(x / TILESIZE)] == '1');
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
			else
				draw_square(game, x * TILESIZE, y * TILESIZE, 0xFFFFFF);
			x++;
		}
		y++;
	}
}
