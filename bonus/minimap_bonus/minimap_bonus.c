/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:23:29 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/13 14:40:09 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"

void minimap_pixel_put(t_minimap *minimap, int x, int y, int color)
{
	char *pixel;

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
		while (x < minimap->width)
		{
			minimap_pixel_put(minimap, x, y, 0x55000000);
			x++;
		}
		y++;
	}
}

void	calculate_visible_map_range(t_game *game, int *ranges)
{
	ranges[0] = game->minimap.width - WINDOW_WIDTH;
}

int render_minimap(void *game_)
{
	t_game *game;

	game = game_;
	int ranges[4]; // [start_map_x, end_map_x, start_map_y, end_map_y]	
	clear_minimap_background(&game->minimap);
	
	calculate_visible_map_range(game, ranges);

	// draw_visible_map_cells(game, ranges);
	
	// draw_player_marker(game);
	
	// draw_player_direction(game);
	
	// draw_minimap_border(&game->minimap);
	return(0);
}
