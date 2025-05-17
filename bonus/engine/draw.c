/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:32:07 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/17 20:33:11 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	draw_minisquare(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = TILESIZE / 16;
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

void	put_pixel_in_img(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor(t_game *game)
{
	int	x;
	int	y;
	int	mini_size;
	int	start_y;
	int	end_y;

	mini_size = TILESIZE / 16;
	start_y = (ROWS * TILESIZE) / 2;
	end_y = ROWS * TILESIZE;
	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < COLS * TILESIZE)
		{
			draw_minisquare(game, x, y, \
				shade_color(game->parse_data.f, \
				(float)(ROWS * TILESIZE - y), game));
			x += mini_size;
		}
		y += mini_size;
	}
}

unsigned int	shade_sky(unsigned int color, float distance)
{
	float			shade_factor;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	shade_factor = 1.0f / (1.0f + distance * 0.005f);
	r = ((color >> 16) & 0xFF) * shade_factor;
	g = ((color >> 8) & 0xFF) * shade_factor;
	b = (color & 0xFF) * shade_factor;
	return ((r << 16) | (g << 8) | b);
}

void	draw_sky(t_game *game)
{
	int	x;
	int	y;
	int	mini_size;
	int	max_height;

	mini_size = TILESIZE / 16;
	max_height = (ROWS * TILESIZE) / 2;
	y = 0;
	while (y < max_height)
	{
		x = 0;
		while (x < COLS * TILESIZE)
		{
			draw_minisquare(game, x, y, \
				shade_sky(game->parse_data.c, (float)(y)));
			x += mini_size;
		}
		y += mini_size;
	}
}
