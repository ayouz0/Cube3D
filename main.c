/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:00:51 by hfhad             #+#    #+#             */
/*   Updated: 2025/04/27 15:14:36 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
int close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(1);
}

void put_pixel_in_img(t_game *game, int x, int y, int color)
{
	char *dst;

	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_square(t_game *game, int x, int y, int color)
{
	int i, j;

	i = 0;
	while (i < TILESIZE- 1)
	{
		j = 0;
		while (j < TILESIZE - 1)
		{
			put_pixel_in_img(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_map(t_game *game, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (y < 9)
	{
		x = 0;
		while (x < 16)
		{
			if (map[y][x] == '1')
				draw_square(game, x * TILESIZE, y * TILESIZE, 0x404040);
			else
				draw_square(game, x * TILESIZE, y * TILESIZE, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

int	has_wall_at(int x, int y, char **map)
{
	return (map[(int)(y / TILESIZE)][(int)(x / TILESIZE)] == '1');
}

int main()
{
	t_game game;

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
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3d");
	game.img_ptr = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.addr = mlx_get_data_addr(game.img_ptr, &game.bits_per_pixel, &game.line_length, &game.endian);
	render_map(&game, map);
	init_player(&game.player, &game);
	mlx_hook(game.win, 2, 1L<<0, update, &game);
	mlx_put_image_to_window(game.mlx, game.win, game.img_ptr, 0, 0);

	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}