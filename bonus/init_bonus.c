/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:32:33 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/22 09:45:24 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	load_door(t_game *game)
{
	game->load += load_image_and_address(&game->door_opening[0].ptr, game, \
					"bonus/textures/doors/d_open0.xpm", &game->door_opening[0]);
	game->load += load_image_and_address(&game->door_opening[1].ptr, game, \
					"bonus/textures/doors/d_open1.xpm", &game->door_opening[1]);
	game->load += load_image_and_address(&game->door_opening[2].ptr, game, \
					"bonus/textures/doors/d_open2.xpm", &game->door_opening[2]);
	game->load += load_image_and_address(&game->door_opening[3].ptr, game, \
					"bonus/textures/doors/d_open3.xpm", &game->door_opening[3]);
	game->load += load_image_and_address(&game->door_opening[4].ptr, game, \
					"bonus/textures/doors/d_open4.xpm", &game->door_opening[4]);
	game->load += load_image_and_address(&game->door_opening[5].ptr, game, \
					"bonus/textures/doors/d_open5.xpm", &game->door_opening[5]);
	game->load += load_image_and_address(&game->door_button[0].ptr, game, \
					"bonus/textures/doors/button0.xpm", &game->door_button[0]);
	game->load += load_image_and_address(&game->door_button[1].ptr, game, \
					"bonus/textures/doors/button1.xpm", &game->door_button[1]);
	game->load += load_image_and_address(&game->door_button[2].ptr, game, \
					"bonus/textures/doors/button2.xpm", &game->door_button[2]);
	game->load += load_image_and_address(&game->door_button[3].ptr, game, \
					"bonus/textures/doors/button3.xpm", &game->door_button[3]);
	game->load += load_image_and_address(&game->door_button[4].ptr, game, \
					"bonus/textures/doors/button4.xpm", &game->door_button[4]);
	game->load += load_image_and_address(&game->door_button[5].ptr, game, \
					"bonus/textures/doors/button5.xpm", &game->door_button[5]);
}

int	init_door(t_game *game)
{
	game->door_state = 0;
	game->door_open = 0;
	game->ray.door.door_num = 0;
	game->has_button = 0;
	load_door(game);
	if (game->load)
		return (1);
	return (0);
}

int	init_light(t_game *game)
{
	game->light = 2;
	game->direction = 1;
	game->load += load_image_and_address(&game->light_img[0].ptr, game, \
					"bonus/textures/fire_1.xpm", &game->light_img[0]);
	game->load += load_image_and_address(&game->light_img[1].ptr, game, \
					"bonus/textures/fire_2.xpm", &game->light_img[1]);
	game->load += load_image_and_address(&game->light_img[2].ptr, game, \
					"bonus/textures/fire_3.xpm", &game->light_img[2]);
	game->load += load_image_and_address(&game->light_img[3].ptr, game, \
					"bonus/textures/fire_4.xpm", &game->light_img[3]);
	game->load += load_image_and_address(&game->light_img[4].ptr, game, \
					"bonus/textures/fire_5.xpm", &game->light_img[4]);
	game->load += load_image_and_address(&game->light_img[5].ptr, game, \
					"bonus/textures/fire_6.xpm", &game->light_img[5]);
	game->load += load_image_and_address(&game->light_img[6].ptr, game, \
					"bonus/textures/fire_7.xpm", &game->light_img[6]);
	game->load += load_image_and_address(&game->light_img[7].ptr, game, \
					"bonus/textures/fire_8.xpm", &game->light_img[7]);
	game->load += load_image_and_address(&game->door_tex.ptr, game, \
					"bonus/textures/door.xpm", &game->door_tex);
	if (game->load)
		return (1);
	return (0);
}

void	init_logic(t_game *game)
{
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.s = 0;
	game->keys.w = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.esc = 0;
	game->is_healed = 1;
	game->stamina = 320;
	game->show_minimap = 1;
	game->mouse.mouse_down = 0;
}
