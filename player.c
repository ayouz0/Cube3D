/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:48 by hfhad             #+#    #+#             */
/*   Updated: 2025/04/27 15:33:31 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *map[] = {
	"1111111111111111",
	"1000000000000001",
	"1000111000000001",
	"1000001000000001",
	"1000001000111001",
	"1000001000001001",
	"1000000000001001",
	"1000000000000001",
	"1111111111111111",
	NULL
};

void draw_player(t_game *game, int x, int y, int radius, int color)
{
	int i;
	int	j;
	int	dx;
	int	dy;

	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			dx = i;
			dy = j;
			if (dx * dx + dy * dy <= radius * radius)
				put_pixel_in_img(game, x + dx, y + dy, color);
			j++;
		}
		i++;
	}
}

void draw_line(t_game *game, t_player *player, int x, int y, int line_length, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int e2;

	printf("inside draw line angle = %f\n", player->mv.player_angle);
	player->mv.dir_y = sin(player->mv.player_angle);
	player->mv.dir_x = cos(player->mv.player_angle);
	player->mv.end_x = (int)(x + player->mv.dir_x * line_length);
	player->mv.end_y = (int)(y + player->mv.dir_y * line_length);
	dx = abs(player->mv.end_x - x);
	dy = abs(player->mv.end_y - y);
	sx = x < player->mv.end_x ? 1 : -1;
	sy = y < player->mv.end_y ? 1 : -1;
	player->mv.err = dx - dy;
	while (1)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			put_pixel_in_img(game, x, y, color);
		}
		if (x == player->mv.end_x && y == player->mv.end_y) // Fixed condition
			break;
		e2 = player->mv.err * 2;
		if (e2 > -dy)
		{
			player->mv.err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			player->mv.err += dx;
			y += sy;
		}
	}
}

void clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_in_img(game, x, y, 0x000000); // black
			x++;
		}
		y++;
	}
}

int	update(int key, t_game *game)
{
	float	movestep;

	game->player.mv.turndir = 0;
	game->player.mv.walkdir = 0;
	printf("key =%d\n", key);
	if (key == 53)
		close_window(game);
	else if (key == 124 ) // ->
	{
		printf("key=%d\n", key);
		game->player.mv.turndir = 1;
		game->player.mv.player_angle += (game->player.mv.turndir * game->player.mv.mov_speed) * (M_PI / 180);
	}
	else if (key == 123) // <-
	{
		printf("key=%d\n", key);
		game->player.mv.turndir = -1;
		game->player.mv.player_angle += (game->player.mv.turndir * game->player.mv.mov_speed) * (M_PI / 180);
	}
	else if (key == 1) //D
	{
		game->player.player_x -= game->player.mv.mov_speed;
	}
	else if (key == 0) // A
	{
		game->player.player_x += game->player.mv.mov_speed;
	}
	else if (key == 1) // S
	{
		printf("key=%d\n", key);
		
	}
	else if (key == 13) // W
	{
		printf("key=%d\n", key);
		game->player.mv.walkdir = 1;
		movestep = game->player.mv.walkdir * game->player.mv.mov_speed;
		game->player.mv.player_angle += (game->player.mv.turndir * game->player.mv.mov_speed) * (M_PI / 180);
		game->player.player_x += cos(game->player.mv.player_angle) * game->player.mv.mov_speed;
		game->player.player_y += sin(game->player.mv.player_angle) * game->player.mv.mov_speed;
	}
	clear_image(game);
	render_map(game, map);
	draw_player(game, game->player.player_x, game->player.player_y, 6, 0xFF0000);
	draw_line(game, &game->player ,game->player.player_x, game->player.player_y, 32, 0xFF0000);
	mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
	return (0);
}

void    init_player(t_player *player, t_game *game)
{
	player->player_x = WINDOW_WIDTH / 2;
	player->player_y = WINDOW_HEIGHT / 2;
	player->mv.turndir = 0; // if 1 rotate to right -1 rotating to left 0 not rotating
	player->mv.walkdir = 0; // 0 not moving 1 moving forward -1 moving backwords
	player->mv.player_angle = 0; //50 * M_PI / 180;
	player->mv.mov_speed = 2.5;
	player->mv.rotspeed = 2 * (M_PI / 180);
	draw_player(game, player->player_x, player->player_y, 6, 0xFF0000);
	draw_line(game, player ,player->player_x, player->player_y, 32, 0xFF0000);
}