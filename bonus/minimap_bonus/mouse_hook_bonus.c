/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:20 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/23 13:05:11 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"

int	pressed(int key, int x, int y, void *game_)
{
	t_game	*game;

	game = game_;
	if (key == 1)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			game->mouse.mouse_down = 1;
			game->mouse.x = x;
		}
	}
	return (1);
}

int	released(int key, int x, int y, void *game_)
{
	t_game	*game;

	(void)y;
	(void)key;
	game = game_;
	game->mouse.mouse_down = 0;
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		game->mouse.x = x;
	return (1);
}

int	mouse_movement_handeling(int x, int y, void *game_)
{
	t_game	*game;

	(void)y;
	game = game_;
	if (!game->mouse.mouse_down)
		return (1);
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return (1);
	if (x > game->mouse.x)
		game->player.mv.player_angle += MOUSE_ANGLE;
	else if (x < game->mouse.x)
		game->player.mv.player_angle -= MOUSE_ANGLE;
	game->mouse.x = x;
	return (0);
}
