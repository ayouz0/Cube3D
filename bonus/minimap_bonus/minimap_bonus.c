/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:23:29 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/20 20:44:52 by aaitabde         ###   ########.fr       */
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

void	bresenham_line(t_game *game, t_line_ctx *l)
{
	int	x;
	int	y;
	int	e2;

	x = l->start_x;
	y = l->start_y;
	while (1)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			minimap_pixel_put(&game->minimap, x, y, game->parse_data.f + 0xaedb09);
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

void	draw_line(t_game *game, int start_x, int start_y)
{
	t_line_ctx l;

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
	bresenham_line(game, &l);
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

int render_minimap(void *game_)
{
	t_game	*game;

	game = game_;
	if (!game->show_minimap)
		return (0);
	if (game->minimap.cell_size < 6 || game->minimap.cell_size > 15)
		game->minimap.cell_size = 10;
	game->minimap.width = game->minimap.view_range * 2 * game->minimap.cell_size;
	game->minimap.height = game->minimap.view_range * 2 * game->minimap.cell_size;
	game->minimap.pos_x = WINDOW_WIDTH - game->minimap.width - MINIMAP_PAD;
	mlx_destroy_image(game->mlx, game->minimap.minimap_img);
	game->minimap.minimap_img = mlx_new_image(game->mlx,
										 game->minimap.width,
										 game->minimap.height);
	game->minimap.addr = mlx_get_data_addr(game->minimap.minimap_img,
						&game->minimap.bits_per_pixel, &game->minimap.line_length,
						&game->minimap.endian);
	clear_minimap_background(game);
	draw_visible_map_cells(game);
	draw_player_marker(game);
	draw_stamina_bar(game);
	
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.minimap_img, 
						game->minimap.pos_x, game->minimap.pos_y);
	return (0);
}
