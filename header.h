/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:02:19 by hfhad             #+#    #+#             */
/*   Updated: 2025/04/27 13:10:22 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H


#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


# define TILESIZE  32
# define ROWS 9
# define COLS 16
# define FOV (60 * M_PI /180) // degre to radian
# define WINDOW_WIDTH (COLS * TILESIZE)
# define WINDOW_HEIGHT (ROWS * TILESIZE)
# define RES 4
# define NUM_RAYS (WINDOW_WIDTH / RES) // nrays = (screen_with / res)

typedef struct s_moves
{
	float	player_angle;
	float	dir_x;
	float	dir_y;
	int		end_x;
	int		end_y;
	int		err;
}	t_moves;

typedef struct s_player
{
	t_moves	mv;
	int		player_x;
	int		player_y;
	int		turndir;
	int		walkdir;
	int		rotang;
	int		mov_speed;
} 	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img_ptr;
	char		*addr;
	t_player	player;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
} t_game;

void    init_player(t_player *player, t_game *game);
void	put_pixel_in_img(t_game *game, int x, int y, int color);

#endif