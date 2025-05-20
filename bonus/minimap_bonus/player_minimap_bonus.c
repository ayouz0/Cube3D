/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_minimap_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:58:18 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/20 21:59:34 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"

static void	bresenham_line_algo(t_game *game, t_line_ctx *l)
{
	int	x;
	int	y;
	int	e2;

	x = l->start_x;
	y = l->start_y;
	while (1)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			minimap_pixel_put(&game->minimap, x, y, \
			game->parse_data.f + 0xaedb09);
		if (x == l->end_x && y == l->end_y)
			break ;
		e2 = l->err;
		if (e2 > -l->delta_x)
		{
			l->err -= l->delta_y;
			x += l->sx;
		}
		if (e2 < l->delta_y)
		{
			l->err += l->delta_x;
			y += l->sy;
		}
	}
}

static void	draw_line(t_game *game, int start_x, int start_y)
{
	t_line_ctx	l;

	l.start_x = start_x;
	l.start_y = start_y;
	game->player.mv.dir_x = cos(game->player.mv.player_angle);
	game->player.mv.dir_y = sin(game->player.mv.player_angle);
	l.end_x = l.start_x + game->player.mv.dir_x * game->minimap.cell_size;
	l.end_y = l.start_y + game->player.mv.dir_y * game->minimap.cell_size;
	l.delta_x = abs(l.end_x - l.start_x);
	l.delta_y = abs(l.end_y - l.start_y);
	l.sx = -1;
	if (l.start_x < l.end_x)
		l.sx = 1;
	l.sy = -1;
	if (l.start_y < l.end_y)
		l.sy = 1;
	l.err = -l.delta_y / 2;
	if (l.delta_x > l.delta_y)
		l.err = l.delta_x / 2;
	bresenham_line_algo(game, &l);
}

// this is a circle equation
// it checks if the point (i, j) is inside the circle
// with center (0, 0) and radius size
// if the pont is inside the circle, it draws it
void	draw_player_marker(t_game *game)
{
	int	center_x;
	int	center_y;
	int	size;
	int	i;
	int	j;

	center_x = game->minimap.width / 2;
	center_y = game->minimap.height / 2;
	size = game->minimap.cell_size / 3;
	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			if (i * i + j * j <= size * size)
				minimap_pixel_put(&game->minimap, center_x + i, \
				center_y + j, game->parse_data.f + 0xaedb09);
			j++;
		}
		i++;
	}
	draw_line(game, center_x, center_y);
}
