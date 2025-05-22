/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:12:37 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/22 09:44:39 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_bonus.h"

int	get_intercept(t_ray *ray, int hit_type)
{
	if (hit_type == 2)
	{
		ray->horz_hit_is_door = 2;
		ray->door.y = ray->next_horz_y;
		ray->door.x = ray->next_horz_x;
		ray->door.door_num++;
		return (0);
	}
	else if (hit_type == 1)
	{
		ray->found_horz_hit = 1;
		ray->horz_hit_x = ray->next_horz_x;
		ray->horz_hit_y = ray->next_horz_y;
		ray->horz_hit_is_door = 0;
		return (1);
	}
	return (-1);
}

void	render_door_slice(t_game *game, t_ray *ray, int ray_id, float wall_dist)
{
	int		wall_height;
	float	corrected_dist;
	float	proj_plane_dist;
	float	actual_dist;

	if ((ray->door.y / TILESIZE) >= 0 && (ray->door.x / TILESIZE) >= 0 && \
	game->map[(int)(ray->door.y / TILESIZE)][(int)(ray->door.x / TILESIZE)] \
	== 'D')
	{
		actual_dist = distance_between_points(ray->door.x, ray->door.y, \
						game->player.player_x, game->player.player_y);
		corrected_dist = actual_dist * \
			cos(ray->ray_angle - game->player.mv.player_angle);
		proj_plane_dist = (WINDOW_WIDTH / 2) / tan(FOV / 2);
		wall_height = (TILESIZE / corrected_dist) * proj_plane_dist;
		if (actual_dist < wall_dist)
			draw_door_column(game, ray, ray_id, wall_height);
		ray->door.door_num--;
	}
	ray->door.y -= ray->door.dy;
	ray->door.x -= ray->door.dx;
}
