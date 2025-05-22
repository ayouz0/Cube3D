/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:10:31 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/22 09:45:01 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H
# include "../header_bonus.h"

void	init_minimap(t_game *game);
int		render_minimap(void *game_);
int		pressed(int key, int x, int y, void *game_);
int		released(int key, int x, int y, void *game_);
int		mouse_movement_handeling(int x, int y, void *game_);
void	draw_player_marker(t_game *game);
void	minimap_pixel_put(t_minimap *minimap, int x, int y, int color);

typedef struct s_pixel_ctx
{
	int	real_y;
	int	real_x;
	int	x;
	int	y;
}	t_pixel_ctx;

typedef struct s_line_ctx
{
	int	delta_x;
	int	delta_y;
	int	err;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	sx;
	int	sy;
}	t_line_ctx;

# define MINIMAP_PAD 6
# define BORDER_THICKNESS 4
# define LINE_LENGHT 20
# define MOUSE_ANGLE 0.07

#endif