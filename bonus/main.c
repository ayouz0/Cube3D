/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:00:51 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/18 16:40:18 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(1);
}

void	leaks()
{
	system("leaks -q cub3D");
}

void	handle_stamina(t_game *game)
{
	long		current_time;
	current_time = get_current_time_ms();
	if (game->player.mv.mov_speed == 8 && current_time >= 500 && game->stamina != 0)
	{
		game->stamina--;
		if (game->stamina == 0)
			game->is_healed = 0;
	}
	if ((game->stamina == 0 || game->player.mv.mov_speed == 3.5) && current_time >= 500 && game->is_healed != 1)
	{
		game->stamina++;
		if (game->stamina == 320)
			game->is_healed = 1;
	}
	if (game->is_healed == 0)
		game->player.mv.mov_speed = 3.5;
}

int combined_update(t_game *game)
{
	handle_stamina(game);
	update(game);
	render_minimap(game);
	return (0);
}

int	pressed(int key, int x, int y, void *game_)
{
	t_game *game;

	(void)x;
	(void)y;
	game = game_;
	if (key == 1)
	{
		game->mouse.mouse_down = 1;
		game->mouse.x = x;
	}
	return (1);
}
int	released(int key, int x, int y, void *game_)
{
	t_game *game;

	(void)y;
	(void)key;
	game = game_;
	game->mouse.mouse_down = 0;
	game->mouse.x = x;
	return (1);
}

int	mouse_movement_handeling(int x, int y, void *game_)
{
	t_game *game;

	(void)y;
	game = game_;
	if (!game->mouse.mouse_down)
		return (1);
	if (x > game->mouse.x)
		game->player.mv.player_angle += MOUSE_ANGLE;
	else if (x < game->mouse.x)
		game->player.mv.player_angle -= MOUSE_ANGLE;
	game->mouse.x = x;
	return(0);
}

int	game_setup(t_game *game)
{
	init_logic(game);
	init_player(&game->player, game);
	init_minimap(game);
	init_door(game);
	init_light(game);
	return (0);
}

void	game_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
	mlx_hook(game->win, 3, 1L<<1, key_release, game);
	mlx_loop_hook(game->mlx, combined_update, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 4, 1, pressed, game);
	mlx_hook(game->win, 5, 1, released, game);
	mlx_hook(game->win, 6, 1, mouse_movement_handeling, game);
}

int main(int ac, char **av)
{
	t_game	game;
	(void)av;
	(void)ac;
	atexit(leaks);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (printf("Error: mlx initialization failed\n"), 1);
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
	game_setup(&game);
	game_hooks(&game);
	mlx_loop(game.mlx);
}
