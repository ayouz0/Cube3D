/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:00:51 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/21 16:03:04 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(1);
}

void	init_keys(t_game *game)
{
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.s = 0;
	game->keys.w = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.esc = 0;
}

int	main(int ac, char **av)
{
	t_game	game;

	(void)av;
	(void)ac;
	game.mlx = mlx_init();
	if (!game.mlx)
		return (NULL);
	game.parse_data.no.ptr = NULL;
	game.parse_data.so.ptr = NULL;
	game.parse_data.we.ptr = NULL;
	game.parse_data.ea.ptr = NULL;
	if (parsing(ac, av, &game) != 0)
		(free_parse_data(&game), exit(1));
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3d");
	game.img_ptr = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.addr = mlx_get_data_addr(game.img_ptr, \
				&game.bits_per_pixel, &game.line_length, &game.endian);
	init_player(&game.player, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_put_image_to_window(game.mlx, game.win, game.img_ptr, 0, 0);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}
