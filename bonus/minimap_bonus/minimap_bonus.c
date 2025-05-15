 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:23:29 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/14 17:01:21 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"

void minimap_pixel_put(t_minimap *minimap, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= minimap->width || y >= minimap->height)
		return;
	pixel = minimap->addr + (y * minimap->line_length + 
						   x * (minimap->bits_per_pixel / 8));
	*(int*)pixel = color;
}

void clear_minimap_background(t_minimap *minimap)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < minimap->height)
	{
		x = 0;
		while (x < minimap->width)
		{
			minimap_pixel_put(minimap, x, y, 0x55000000);
			x++;
		}
		y++;
	}
}

// this is a circle equation, it checks if the point (i, j) is inside the circle
// with center (0, 0) and radius size. If the point is inside the circle, it draws
void draw_player_marker(t_game *game)
{
	int center_x;
	int center_y;
	int size;
	int i;
	int j;

	center_x = game->minimap.width / 2;
	center_y = game->minimap.height / 2;
	size = game->minimap.cell_size / 3;
	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			if (i*i + j*j <= size*size)
				minimap_pixel_put(&game->minimap, center_x + i, center_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void draw_visible_map_cells(t_game *game)
{
	int real_x;
	int real_y;
	int	x;
	int	y;
	(void)game;

	(1) && (real_x = 0, real_y = 0);
	(1) && (x = 0, y = 0);
	while ( x < game->minimap.width)
	{
		real_x = (int)game->player.player_x - TILESIZE * game->minimap.view_range + (x * TILESIZE) / game->minimap.cell_size;
		y = 0;
		while (y < game->minimap.height)
		{
			real_y = (int)game->player.player_y - TILESIZE * game->minimap.view_range + (y * TILESIZE) / game->minimap.cell_size;
			if (real_y / TILESIZE < 0 || real_y / TILESIZE >= game->parse_data.height \
				|| real_x / TILESIZE < 0 || real_x / TILESIZE >= game->parse_data.width)
				minimap_pixel_put(&game->minimap, x, y, 0xFFFF00);
			else if (game->map[real_y / TILESIZE][real_x / TILESIZE] == '1')
				minimap_pixel_put(&game->minimap, x, y, 0xC0C0C0);
			else if (game->map[real_y / TILESIZE][real_x / TILESIZE] == 'D')
				minimap_pixel_put(&game->minimap, x, y, 0x00FFFF);
			else if (game->map[real_y / TILESIZE][real_x / TILESIZE] == ' ')
				minimap_pixel_put(&game->minimap, x, y, 0x00FFFF);
			y++;
		}
		x++;
	}
}
void draw_minimap_border(t_minimap *minimap)
{
	int	y;
	int	x;
	int	border;

	(1) && (y = minimap->height - 1, x = minimap->width - 1);
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
		{
			minimap_pixel_put(minimap, border, y, 0xFFFFFF);
			minimap_pixel_put(minimap, minimap->width - 1 - border, y, 0xFFFFFF);
		}
		y--;
	}
}

int render_minimap(void *game_)
{
	t_game	*game;

	game = game_;
	clear_minimap_background(&game->minimap);

	draw_visible_map_cells(game);
	
	draw_player_marker(game);
	// draw_player_direction(game);
	
	draw_minimap_border(&game->minimap);
	return(0);
}
