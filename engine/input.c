/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:04:09 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/04 17:00:31 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int key_press(int key, t_game *game)
{
	if (key == 53) // Escape
		close_window(game);
	else if (key == 13)  // W
		game->keys.w = 1;
	else if (key == 1)   // S
		game->keys.s = 1;
	else if (key == 0)   // A
		game->keys.a = 1;
	else if (key == 2)   // D
		game->keys.d = 1;
	else if (key == 123) // Left Arrow
		game->keys.left = 1;
	else if (key == 124) // Right Arrow
		game->keys.right = 1;
	return (0);
}

int key_release(int key, t_game *game)
{
	if (key == 13)      // W
		game->keys.w = 0;
	else if (key == 1)  // S
		game->keys.s = 0;
	else if (key == 0)  // A
		game->keys.a = 0;
	else if (key == 2)  // D
		game->keys.d = 0;
	else if (key == 123) // Left Arrow
		game->keys.left = 0;
	else if (key == 124) // Right Arrow
		game->keys.right = 0;
	return (0);
}
