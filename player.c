/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:48 by hfhad             #+#    #+#             */
/*   Updated: 2025/04/27 16:15:13 by hfhad            ###   ########.fr       */
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

int update(t_game *game)
{
	float	movestep;
	float	strafe_angle;

	// Rotation
	if (game->keys.left)
		game->player.mv.player_angle -= game->player.mv.rotspeed;
	if (game->keys.right)
		game->player.mv.player_angle += game->player.mv.rotspeed;

	// Movement
	if (game->keys.w)
	{
		movestep = game->player.mv.mov_speed;
		game->player.player_x += cos(game->player.mv.player_angle) * movestep;
		game->player.player_y += sin(game->player.mv.player_angle) * movestep;
	}
	if (game->keys.s)
	{
		movestep = game->player.mv.mov_speed;
		game->player.player_x += cos(game->player.mv.player_angle) * movestep * -1;
		game->player.player_y += sin(game->player.mv.player_angle) * movestep * -1;
	}
	if (game->keys.a)
	{
		strafe_angle = game->player.mv.player_angle - M_PI / 2;
		game->player.player_x += cos(strafe_angle) * game->player.mv.mov_speed;
		game->player.player_y += sin(strafe_angle) * game->player.mv.mov_speed;
	}
	if (game->keys.d)
	{
		strafe_angle = game->player.mv.player_angle + M_PI / 2;
		game->player.player_x += cos(strafe_angle) * game->player.mv.mov_speed;
		game->player.player_y += sin(strafe_angle) * game->player.mv.mov_speed;
	}

	// Normalize angle to [0, 2π)
	if (game->player.mv.player_angle >= 2 * M_PI)
		game->player.mv.player_angle -= 2 * M_PI;
	else if (game->player.mv.player_angle < 0)
		game->player.mv.player_angle += 2 * M_PI;

	// printf("After update: angle=%f, x=%f, y=%f\n", game->player.mv.player_angle, game->player.player_x, game->player.player_y);
	clear_image(game);
	render_map(game, map);
	draw_player(game, (int)game->player.player_x, (int)game->player.player_y, 6, 0xFF0000);
	draw_line(game, &game->player, (int)game->player.player_x, (int)game->player.player_y, 32, 0xFF0000);
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
	player->mv.mov_speed = 1;
	player->mv.rotspeed = 5 * (M_PI / 180);
	draw_player(game, (int)player->player_x, (int)player->player_y, 6, 0xFF0000);
	draw_line(game, player ,(int)player->player_x, (int)player->player_y, 32, 0xFF0000);
}