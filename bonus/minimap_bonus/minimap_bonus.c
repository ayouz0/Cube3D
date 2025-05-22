/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:23:29 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/22 09:57:45 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"

void	minimap_pixel_put(t_minimap *minimap, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= minimap->width || y >= minimap->height)
		return ;
	pixel = minimap->addr + (y * minimap->line_length + \
						x * (minimap->bits_per_pixel / 8));
	*(int *)pixel = color;
}

void	clear_minimap_background(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->minimap.height)
	{
		x = 0;
		while (x < game->minimap.width)
		{
			minimap_pixel_put(&game->minimap, x, y, game->parse_data.f);
			x++;
		}
		y++;
	}
}

void	draw_stamina_bar(t_game *game)
{
	int	x;
	int	y;
	int	thickness;

	x = 0;
	y = 0;
	while (x <= game->stamina / 2)
	{
		thickness = 5;
		while (thickness > 0)
		{
			if (game->is_healed)
				minimap_pixel_put(&game->minimap, x, \
				game->minimap.height - thickness, 0x008000);
			else
				minimap_pixel_put(&game->minimap, x, \
				game->minimap.height - thickness, 0x008000 - game->stamina / 2);
			thickness--;
		}
		x++;
	}
}

int	render_minimap(void *game_)
{
	t_game	*game;

	game = game_;
	if (!game->show_minimap)
		return (0);
	if (game->minimap.cell_size < 6 || game->minimap.cell_size > 15)
		game->minimap.cell_size = 10;
	game->minimap.width = game->minimap.view_range * 2 * \
	game->minimap.cell_size;
	game->minimap.height = game->minimap.view_range * 2 * \
	game->minimap.cell_size;
	game->minimap.pos_x = WINDOW_WIDTH - game->minimap.width - MINIMAP_PAD;
	mlx_destroy_image(game->mlx, game->minimap.minimap_img);
	game->minimap.minimap_img = mlx_new_image(game->mlx, \
								game->minimap.width, \
								game->minimap.height);
	game->minimap.addr = mlx_get_data_addr(game->minimap.minimap_img, \
						&game->minimap.bits_per_pixel, \
						&game->minimap.line_length, &game->minimap.endian);
	clear_minimap_background(game);
	draw_visible_map_cells(game);
	(draw_player_marker(game), draw_stamina_bar(game));
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.minimap_img, \
						game->minimap.pos_x, game->minimap.pos_y);
	return (0);
}
