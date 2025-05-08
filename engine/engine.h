/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:02:19 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/07 17:31:45 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ENGINE_H
# define ENGINE_H


#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// #include "../parsing/parsing.h"
// #include "../header.h"

# define TILESIZE  80
# define ROWS 9
# define COLS 16
# define FOV (60 * M_PI /180) // degre to radian
# define WINDOW_WIDTH (COLS * TILESIZE)
# define WINDOW_HEIGHT (ROWS * TILESIZE)
# define RES 2
# define NUM_RAYS (WINDOW_WIDTH / RES) // nrays = (screen_with / res)
# define PLAYER_RADIUS 1.0f

typedef struct s_cardinals
{
	void	*ptr;
	int		h;
	int		w;
}	t_cardinals;

typedef struct s_parser
{
	char		**map;
	int			fd;
	t_cardinals	NO;
	t_cardinals	SO;
	t_cardinals	WE;
	t_cardinals	EA;
	int			width;
	int			height;
	int			f;
	int			c;
} t_parser;

typedef struct s_moves
{
	float	player_angle;
	float	dir_x;
	float	dir_y;
	float	turndir;
	float	walkdir;
	float	mov_speed;
	float	rotspeed;
	int		end_x;
	int		end_y;
	int		err;
}	t_moves;

typedef struct s_player
{
	t_moves	mv;
	float		player_x;
	float		player_y;
} 	t_player;

typedef struct s_ray
{
	float ray_angle;     // angle of the ray
	float wall_hit_x;     // where the wall was hit (x)
	float wall_hit_y;     // where the wall was hit (y)
	float distance;       // distance to wall
	int   was_hit_vertical; // 1 if vertical wall was hit, 0 if horizontal
} t_ray;


typedef struct	s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img_ptr;
	char		*addr;
	t_player	player;
	t_keys		keys;
	t_parser	parse_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**map;
	char		*error_msg;
} t_game;



unsigned int shade_color(unsigned int color, float distance);
void	draw_floor(t_game *game);
void	draw_sky(t_game *game);
void	render_map(t_game *game, char **map);
void	init_player(t_player *player, t_game *game);
void	put_pixel_in_img(t_game *game, int x, int y, int color);
int		close_window(t_game *game);
int		update(t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
void	draw_player(t_game *game, int x, int y, int radius, int color);
void	draw_line(t_game *game, t_player *player, int x, int y, int line_length, int color);
void	clear_image(t_game *game);
float	normalize_angle(float angle);
int		has_wall_at(int x, int y, t_game *game);
void	cast_all_rays(t_game *game, t_ray *ray);

#endif