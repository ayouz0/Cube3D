/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:04:09 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/16 19:42:55 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	key_press(int key, t_game *game)
{

	printf("key=%d\n", key);
	if (key == 53)
		close_window(game);
	if (key == 49)
	{
		if (game->door_state <= 5 && game->door_state > 0 && game->door_open == 1)
		{
			game->door_state--;
			if (game->door_state == 0)
				game->door_open = 0;
		}
		else if (game->door_open == 0)
			game->door_state++;
		if (game->door_state == 5)
			game->door_open = 1;
		printf("door state == %d\n", game->door_state);
		printf("full open == %d\n", game->door_open);
	}
	else if (key == 3)
		game->light++;
	else if (key == 13)
		game->keys.w = 1;
	else if (key == 1)
		game->keys.s = 1;
	else if (key == 0)
		game->keys.a = 1;
	else if (key == 2)
		game->keys.d = 1;
	else if (key == 123)
		game->keys.left = 1;
	else if (key == 124)
		game->keys.right = 1;
	else if (key == 257 && game->is_healed == 1)
		game->player.mv.mov_speed = 8;
	else if (key == 46)
		game->show_minimap = !game->show_minimap;
	game->minimap.cell_size += (key == 126) + (- (key == 125));
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 13)
		game->keys.w = 0;
	else if (key == 1)
		game->keys.s = 0;
	else if (key == 0)
		game->keys.a = 0;
	else if (key == 2)
		game->keys.d = 0;
	else if (key == 123)
		game->keys.left = 0;
	else if (key == 124)
		game->keys.right = 0;
	else if (key == 257)
		game->player.mv.mov_speed = 3.5;
	return (0);
}
