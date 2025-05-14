/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:02:19 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/14 12:42:03 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# define TILESIZE 80
# define ROWS 9
# define COLS 16
# define FOV (60 * M_PI /180)
# define WINDOW_WIDTH (COLS * TILESIZE)
# define WINDOW_HEIGHT (ROWS * TILESIZE)
# define RES 1
# define NUM_RAYS (WINDOW_WIDTH / RES)
# define PLAYER_RADIUS 1.0f

typedef struct s_cardinals
{
	void	*ptr;
	int		h;
	int		w;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_cardinals;

typedef struct	s_door
{
	int			x;
	int			y;
	t_cardinals	texture;
}	t_door;

typedef struct s_parser
{
	char		**map;
	int			fd;
	t_cardinals	no;
	t_cardinals	so;
	t_cardinals	we;
	t_cardinals	ea;
	int			width;
	int			height;
	int			f;
	int			c;
}	t_parser;


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
	float	player_x;
	float	player_y;
}	t_player;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	float	horz_hit_x;
	float	horz_hit_y;
	float	vert_hit_x;
	float	vert_hit_y;
	int		found_horz_hit;
	int		found_vert_hit;
	float	next_horz_x;
	float	next_horz_y;
	float	next_vert_x;
	float	next_vert_y;
}	t_ray;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_keys;

typedef struct s_minimap
{
	void	*minimap_img;
	char	*addr;
	int		bits_per_pixel;
    int		line_length;
    int		endian;
	int		width;
	int		height;
	int		cell_size;
	int		pos_x;
	int		pos_y;
	int		view_range;
} t_minimap;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img_ptr;
	char		*addr;
	float		fov;
	t_player	player;
	t_keys		keys;
	t_parser	parse_data;
	t_ray		ray;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**map;
	int			light;
	t_door		*doors;
	int			door_count;
	t_cardinals	light_img[8];
	t_minimap	minimap;
}	t_game;

typedef struct s_column_params
{
	int			x;
	int			tex_x;
	int			i;
	int			top;
	int			bottom;
	t_cardinals	*texture;
}	t_column_params;

void	draw_floor(t_game *game);
void	draw_sky(t_game *game);
void	init_player(t_player *player, t_game *game);
void	put_pixel_in_img(t_game *game, int x, int y, int color);
int		close_window(t_game *game);
int		update(t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
void	clear_image(t_game *game);
float	norma_angle(float angle);
int		has_wall_at(int x, int y, t_game *game);
void	cast_all_rays(t_game *game, t_ray *ray);
int		iswall(float x, float y, char **map);
float	distance_between_points(float x1, float y1, float x2, float y2);
void	set_closest_hit(t_ray *ray, float horz_dist, float vert_dist);
void	check_vertical_hit(t_game *game, t_ray *ray,
				int facing_left);
void	check_horizontal_hit(t_game *game, t_ray *ray,
				int facing_up);
void	draw_textured_column(t_game *game, t_ray *ray, int ray_id, int height);
unsigned int	shade_color(unsigned int color, float distance, t_game *game);
void	animate_sprite(t_game *game);

#endif