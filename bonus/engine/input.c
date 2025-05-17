/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:04:09 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/17 12:10:58 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int player_inside_door(t_game *game)
{
    int player_map_x = (int)(game->player.player_x / TILESIZE);
    int player_map_y = (int)(game->player.player_y / TILESIZE);
    
    // Check if any of the 8 surrounding cells (including current cell) is a door
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            int check_y = player_map_y + y;
            int check_x = player_map_x + x;
            
            // Skip invalid coordinates
            if (check_y < 0 || check_x < 0 || !game->map[check_y] || !game->map[check_y][check_x])
                continue;
                
            // If player is near a door
            if (game->map[check_y][check_x] == 'D') {
                // Calculate player's distance to the door center
                float door_center_x = (check_x * TILESIZE) + (TILESIZE / 2);
                float door_center_y = (check_y * TILESIZE) + (TILESIZE / 2);
                float distance = sqrt(pow(game->player.player_x - door_center_x, 2) + 
                                     pow(game->player.player_y - door_center_y, 2));
                
                // If player is very close to the door (adjust threshold as needed)
                if (distance < TILESIZE * 0.7) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int	key_press(int key, t_game *game)
{

	printf("key=%d\n", key);
	if (key == 53)
		close_window(game);
	if (key == 49 && game->has_button) // Space key
	{
		if (game->door_state <= 5 && game->door_state > 0 && game->door_open == 1)
		{
			if (!player_inside_door(game))
			{
				game->door_state--;
				if (game->door_state == 0)
					game->door_open = 0;
			}
			else
			{
				//! cant' close door and ur inside it 
				
			}
		}
		else if (game->door_open == 0)
		{
			game->door_state++;
			if (game->door_state == 5)
				game->door_open = 1;
		}
		printf("door state == %d\n", game->door_state);
		printf("full open == %d\n", game->door_open);
	}
	else if (key == 11)
		game->has_button = !game->has_button;
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
