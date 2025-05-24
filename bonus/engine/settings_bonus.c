/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:04:27 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/22 09:44:32 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_bonus.h"

float	norma_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	get_door_texture_x(t_ray *ray)
{
	int	tex_x;

	tex_x = (int)ray->door.x % TILESIZE;
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		tex_x = TILESIZE - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TILESIZE)
		tex_x = TILESIZE - 1;
	return (tex_x);
}

void	draw_door_column(t_game *game, t_ray *ray, int ray_id, int height)
{
	t_column_params	params;

	params.x = ray_id * RES;
	params.tex_x = get_door_texture_x(ray);
	params.texture = &game->door_opening[game->door_state];
	params.top = (WINDOW_HEIGHT / 2) - (height / 2);
	params.bottom = (WINDOW_HEIGHT / 2) + (height / 2);
	if (params.top < 0)
		params.top = 0;
	if (params.bottom > WINDOW_HEIGHT)
		params.bottom = WINDOW_HEIGHT;
	params.i = 0;
	while (params.i < RES)
	{
		draw_column_strip(game, &params, height);
		params.i++;
	}
}
