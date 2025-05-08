/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:00:51 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/08 16:22:24 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void put_pixel_in_img(t_game *game, int x, int y, int color)
{
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return;

	char *dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	leaks(){
	system("leaks -q cub3D");
}

int main(int ac, char **av)
{
	t_game game;
	(void)av;
	(void)ac;
	atexit(leaks);
	game.mlx = mlx_init();
	if (parsing(ac, av, &game) != 0)
		return (1);
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3d");
	game.img_ptr = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.addr = mlx_get_data_addr(game.img_ptr, &game.bits_per_pixel, &game.line_length, &game.endian);
	game.keys.a = 0;
	game.keys.d = 0;
	game.keys.s = 0;
	game.keys.w = 0;
	game.keys.left = 0;
	game.keys.right= 0;
	game.keys.esc = 0;
	render_map(&game, game.map);
	init_player(&game.player, &game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_put_image_to_window(game.mlx, game.win, game.img_ptr, 0, 0);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}
