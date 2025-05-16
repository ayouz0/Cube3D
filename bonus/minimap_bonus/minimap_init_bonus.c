/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:10:14 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/15 21:46:00 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"

void	init_minimap(t_game *game)
{
	game->minimap.cell_size = 15;
	game->minimap.view_range = 8;
	game->minimap.width = game->minimap.view_range * 2 * game->minimap.cell_size;
	game->minimap.height = game->minimap.view_range * 2 * game->minimap.cell_size;
	game->minimap.pos_x = WINDOW_WIDTH - game->minimap.width - MINIMAP_PAD;
	game->minimap.pos_y = MINIMAP_PAD;
	game->minimap.minimap_img = mlx_new_image(game->mlx, 
										 game->minimap.width, 
										 game->minimap.height);
	game->minimap.addr = mlx_get_data_addr(game->minimap.minimap_img, 
										  &game->minimap.bits_per_pixel, 
										  &game->minimap.line_length, 
										  &game->minimap.endian);
}
