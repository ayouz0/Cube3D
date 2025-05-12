/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:22:44 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/12 14:46:46 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	init_ray_hits(t_ray *ray)
{
	ray->found_horz_hit = 0;
	ray->found_vert_hit = 0;
	ray->horz_hit_x = 0;
	ray->horz_hit_y = 0;
	ray->vert_hit_x = 0;
	ray->vert_hit_y = 0;
}

void	choose_closest_hit(t_game *game, t_ray *ray)
{
	float	horz_dist;
	float	vert_dist;

	if (ray->found_horz_hit)
	{
		horz_dist = distance_between_points(game->player.player_x,
				game->player.player_y, ray->horz_hit_x, ray->horz_hit_y);
	}
	else
		horz_dist = INFINITY;
	if (ray->found_vert_hit)
	{
		vert_dist = distance_between_points(game->player.player_x,
				game->player.player_y, ray->vert_hit_x, ray->vert_hit_y);
	}
	else
		vert_dist = INFINITY;
	set_closest_hit(ray, horz_dist, vert_dist);
}

void	cast_single_ray(t_game *game, t_ray *ray)
{
	int	facing_up;
	int	facing_down;
	int	facing_left;
	int	facing_right;

	ray->ray_angle = norma_angle(ray->ray_angle);
	facing_down = (ray->ray_angle > 0 && ray->ray_angle < M_PI);
	facing_up = !facing_down;
	facing_right = (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI);
	facing_left = !facing_right;
	init_ray_hits(ray);
	check_horizontal_hit(game, ray, facing_up);
	check_vertical_hit(game, ray, facing_left);
	choose_closest_hit(game, ray);
}

void	render_wall_slice(t_game *game, t_ray *ray, int ray_id)
{
	int		wall_height;
	float	corrected_dist;
	float	proj_plane_dist;

	corrected_dist = ray->distance * \
		cos(ray->ray_angle - game->player.mv.player_angle);
	proj_plane_dist = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	wall_height = (TILESIZE / corrected_dist) * proj_plane_dist;
	draw_textured_column(game, ray, ray_id, wall_height);
}

void	cast_all_rays(t_game *game, t_ray *ray)
{
	int		ray_id;
	float	ray_angle;

	ray_id = 0;
	ray_angle = game->player.mv.player_angle - (FOV / 2);
	while (ray_id < NUM_RAYS)
	{
		ray->ray_angle = ray_angle;
		cast_single_ray(game, ray);
		render_wall_slice(game, ray, ray_id);
		ray_angle += FOV / NUM_RAYS;
		ray_id++;
	}
}
