/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drawing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:53:16 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/22 10:04:46 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"

static void	draw_pixel(t_game *game, t_pixel_ctx *pixel)
{
	int	real_x;
	int	real_y;
	int	x;
	int	y;

	real_x = pixel->real_x;
	real_y = pixel->real_y;
	x = pixel->x;
	y = pixel->y;
	if (real_y / TILESIZE < 0 || real_y / TILESIZE >= game->parse_data.height \
		|| real_x / TILESIZE < 0 || real_x / TILESIZE >= game->parse_data.width)
		minimap_pixel_put(&game->minimap, x, y, 0xFFFF00);
	else if (game->map[real_y / TILESIZE][real_x / TILESIZE] == '1')
		minimap_pixel_put(&game->minimap, x, y, game->parse_data.c \
		+ (game->parse_data.c == game->parse_data.f) * 25);
	else if (game->map[real_y / TILESIZE][real_x / TILESIZE] == 'D')
		minimap_pixel_put(&game->minimap, x, y, 0x0 + \
		(game->parse_data.c == game->parse_data.f) * 29);
	else if (game->map[real_y / TILESIZE][real_x / TILESIZE] == ' ')
		minimap_pixel_put(&game->minimap, x, y, 0x00FFFF);
}

static void	draw_column(t_game *game, int x, int real_x)
{
	t_pixel_ctx	pixel;

	pixel.y = 0;
	pixel.x = x;
	pixel.real_x = real_x;
	while (pixel.y < game->minimap.height)
	{
		pixel.real_y = (int)game->player.player_y - TILESIZE * \
		game->minimap.view_range + (pixel.y * TILESIZE) / \
		game->minimap.cell_size;
		draw_pixel(game, &pixel);
		pixel.y++;
	}
}

void	draw_visible_map_cells(t_game *game)
{
	int	real_x;
	int	x;

	real_x = 0;
	x = 0;
	while (x < game->minimap.width)
	{
		real_x = (int)game->player.player_x - TILESIZE * \
		game->minimap.view_range + (x * TILESIZE) / game->minimap.cell_size;
		draw_column(game, x, real_x);
		x++;
	}
}

void	draw_minimap_border(t_minimap *minimap)
{
	int	y;
	int	x;
	int	border;

	y = minimap->height - 1;
	x = minimap->width - 1;
	while (x >= 0)
	{
		border = BORDER_THICKNESS;
		while (--border >= 0)
		{
			minimap_pixel_put(minimap, x, border, 0xFFFFFF);
			minimap_pixel_put(minimap, x, y - border, 0xFFFFFF);
		}
		x--;
	}
	while (y >= 0)
	{
		border = BORDER_THICKNESS;
		while (--border >= 0)
			(minimap_pixel_put(minimap, border, y, 0xFFFFFF), \
			minimap_pixel_put(minimap, minimap->width - 1 - border, \
			y, 0xFFFFFF));
		y--;
	}
}
