/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_image_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:22:27 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/23 15:40:52 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	destroy_light(t_game *game)
{
	if (game->light_img[0].ptr)
		mlx_destroy_image(game->mlx, game->light_img[0].ptr);
	if (game->light_img[1].ptr)
		mlx_destroy_image(game->mlx, game->light_img[1].ptr);
	if (game->light_img[2].ptr)
		mlx_destroy_image(game->mlx, game->light_img[2].ptr);
	if (game->light_img[3].ptr)
		mlx_destroy_image(game->mlx, game->light_img[3].ptr);
	if (game->light_img[4].ptr)
		mlx_destroy_image(game->mlx, game->light_img[4].ptr);
	if (game->light_img[5].ptr)
		mlx_destroy_image(game->mlx, game->light_img[5].ptr);
	if (game->light_img[6].ptr)
		mlx_destroy_image(game->mlx, game->light_img[6].ptr);
	if (game->light_img[7].ptr)
		mlx_destroy_image(game->mlx, game->light_img[7].ptr);
}

void	destroy_door(t_game *game)
{
	if (game->door_opening[0].ptr)
		mlx_destroy_image(game->mlx, game->door_opening[0].ptr);
	if (game->door_opening[1].ptr)
		mlx_destroy_image(game->mlx, game->door_opening[1].ptr);
	if (game->door_opening[2].ptr)
		mlx_destroy_image(game->mlx, game->door_opening[2].ptr);
	if (game->door_opening[3].ptr)
		mlx_destroy_image(game->mlx, game->door_opening[3].ptr);
	if (game->door_opening[4].ptr)
		mlx_destroy_image(game->mlx, game->door_opening[4].ptr);
	if (game->door_opening[5].ptr)
		mlx_destroy_image(game->mlx, game->door_opening[5].ptr);
}

void	destroy_button(t_game *game)
{
	if (game->door_button[0].ptr)
		mlx_destroy_image(game->mlx, game->door_button[0].ptr);
	if (game->door_button[1].ptr)
		mlx_destroy_image(game->mlx, game->door_button[1].ptr);
	if (game->door_button[2].ptr)
		mlx_destroy_image(game->mlx, game->door_button[2].ptr);
	if (game->door_button[3].ptr)
		mlx_destroy_image(game->mlx, game->door_button[3].ptr);
	if (game->door_button[4].ptr)
		mlx_destroy_image(game->mlx, game->door_button[4].ptr);
	if (game->door_button[5].ptr)
		mlx_destroy_image(game->mlx, game->door_button[5].ptr);
}

void	destroy_img(t_game *game)
{
	destroy_light(game);
	destroy_door(game);
	destroy_button(game);
	mlx_destroy_window(game->mlx, game->win);
}
