/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:00:51 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/16 11:17:55 by aaitabde         ###   ########.fr       */
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

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	draw_light_sprite(t_game *game, t_cardinals *sprite, int dest_x, int dest_y)
{
	int		x, y;
	int		color;
	char	*dst;
	int		dst_offset;
	int		src_offset;

	y = 0;
	while (y < sprite->h)
	{
		x = 0;
		while (x < sprite->w)
		{
			src_offset = y * sprite->line_length + x * (sprite->bits_per_pixel / 8);
			color = *(int *)(sprite->addr + src_offset);

			// Optional: skip transparent pixels (e.g., black background)
			if ((color & 0x00FFFFFF) != 0x000000)
			{
				int draw_x = dest_x + x;
				int draw_y = dest_y + y;
				if (draw_x >= 0 && draw_x < WINDOW_WIDTH && draw_y >= 0 && draw_y < WINDOW_HEIGHT)
				{
					dst_offset = draw_y * game->line_length + draw_x * (game->bits_per_pixel / 8);
					dst = game->addr + dst_offset;
					*(int *)dst = color;
				}
			}
			x++;
		}
		y++;
	}
}

void	animate_sprite(t_game *game)
{
	static long	last_update = 0;
	static int	anim_frame = 0;
	static int	direction = 1; // 1 = forward, -1 = backward
	long		current_time;

	if (!game->light)
		return;

	current_time = get_current_time_ms();
	if (current_time - last_update >= 100)
	{
		anim_frame += direction;

		if (anim_frame == 7 || anim_frame == 0)
			direction *= -1; // Reverse direction

		last_update = current_time;
	}

	draw_light_sprite(game, &game->light_img[anim_frame], 14 * 48, 8 * 48);
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
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.minimap_img, 
							game->minimap.pos_x, game->minimap.pos_y);
	return (0);
}

int	init_light(t_game *game)
{
	game->light = 1;
	load_image_and_address(&game->light_img[0].ptr, game, "bonus/textures/fire_1.xpm", &game->light_img[0]);
	load_image_and_address(&game->light_img[1].ptr, game, "bonus/textures/fire_2.xpm", &game->light_img[1]);
	load_image_and_address(&game->light_img[2].ptr, game, "bonus/textures/fire_3.xpm", &game->light_img[2]);
	load_image_and_address(&game->light_img[3].ptr, game, "bonus/textures/fire_4.xpm", &game->light_img[3]);
	load_image_and_address(&game->light_img[4].ptr, game, "bonus/textures/fire_5.xpm", &game->light_img[4]);
	load_image_and_address(&game->light_img[5].ptr, game, "bonus/textures/fire_6.xpm", &game->light_img[5]);
	load_image_and_address(&game->light_img[6].ptr, game, "bonus/textures/fire_7.xpm", &game->light_img[6]);
	load_image_and_address(&game->light_img[7].ptr, game, "bonus/textures/fire_8.xpm", &game->light_img[7]);
	load_image_and_address(&game->door_tex.ptr, game, "bonus/textures/door.xpm", &game->door_tex);
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
	game.is_healed = 1;
	game.keys.door_key = 1;
	game.keys.left = 0;
	game.keys.right= 0;
	game.keys.esc = 0;
	game.stamina = 320;
	game.ray.door.door_num = 0;
	init_player(&game.player, &game);
	init_minimap(&game);
	init_light(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_loop_hook(game.mlx, combined_update, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}
