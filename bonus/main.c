/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:00:51 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/13 14:24:31 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(1);
}

void	leaks(){
	system("leaks -q cub3D");
}

int combined_update(t_game *game)
{
	update(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.minimap_img, 
							game->minimap.pos_x, game->minimap.pos_y);
	return (0);
}

int main(int ac, char **av)
{
	t_game	game;
	(void)av;
	(void)ac;
	atexit(leaks);
	game.mlx = mlx_init();
	game.parse_data.no.ptr = NULL;
	game.parse_data.so.ptr = NULL;
	game.parse_data.we.ptr = NULL;
	game.parse_data.ea.ptr = NULL;
	game.parse_data.fd = -1;
	if (parsing(ac, av, &game) != 0)
		return (free_parse_data(&game), 1);
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
	init_player(&game.player, &game);
	init_minimap(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_loop_hook(game.mlx, combined_update, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}
