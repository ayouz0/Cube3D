/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:03:04 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/16 16:57:37 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	prepare_horizontal_check(t_game *game, t_ray *ray,
				float *x_step, float *y_step)
{
	float	y_intercept;
	float	x_intercept;

	y_intercept = floor(game->player.player_y / TILESIZE) * TILESIZE;
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		y_intercept += TILESIZE;
	x_intercept = game->player.player_x + \
			(y_intercept - game->player.player_y) / tan(ray->ray_angle);
	*y_step = TILESIZE;
	if (!(ray->ray_angle > 0 && ray->ray_angle < M_PI))
		*y_step *= -1;
	*x_step = TILESIZE / tan(ray->ray_angle);
	if ((ray->ray_angle > M_PI_2 && \
		ray->ray_angle < 3 * M_PI_2 && \
		*x_step > 0) || ((ray->ray_angle < M_PI_2 || \
		ray->ray_angle > 3 * M_PI_2) && *x_step < 0))
		*x_step *= -1;
	ray->next_horz_x = x_intercept;
	ray->next_horz_y = y_intercept;
	ray->door.x = x_intercept;
	ray->door.y = y_intercept;
	ray->door.dx = *x_step;
	ray->door.dy = *y_step;
}

void	check_horizontal_hit(t_game *game, t_ray *ray,
				int facing_up)
{
	float	x_step;
	float	y_step;
	int		check_y;
	int		hit_type;
	
	ray->door.facing_up = facing_up;
	prepare_horizontal_check(game, ray, &x_step, &y_step);
	while (ray->next_horz_x >= 0 && \
		ray->next_horz_x <= game->parse_data.width * TILESIZE && \
		ray->next_horz_y >= 0 && \
		ray->next_horz_y <= game->parse_data.height * TILESIZE)
	{
		if (facing_up)
			check_y = ray->next_horz_y - 1;
		else
			check_y = ray->next_horz_y;
		hit_type = has_wall_at(ray->next_horz_x, check_y, game);
		if (hit_type == 2)
		{
			// printf("first     %d  %d  %d  %d\n", ray->door.y, ray->door.x, x_step , y_step);
			ray->horz_hit_is_door = 2;
			ray->door.door_num++;
		}
		else if (hit_type == 1)
		{
			ray->found_horz_hit = 1;
			ray->horz_hit_x = ray->next_horz_x;
			ray->horz_hit_y = ray->next_horz_y;
			ray->horz_hit_is_door = 0;
			return ;
		}
		ray->next_horz_x += x_step;
		ray->next_horz_y += y_step;
	}
}

void	prepare_vertical_check(t_game *game, t_ray *ray,
				float *x_step, float *y_step)
{
	float	x_intercept;
	float	y_intercept;

	x_intercept = floor(game->player.player_x / TILESIZE) * TILESIZE;
	if (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI)
		x_intercept += TILESIZE;
	y_intercept = game->player.player_y + \
			(x_intercept - game->player.player_x) * tan(ray->ray_angle);
	*x_step = TILESIZE;
	if (!(ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI))
		*x_step *= -1;
	*y_step = TILESIZE * tan(ray->ray_angle);
	if ((ray->ray_angle > M_PI && *y_step > 0) || \
		(ray->ray_angle < M_PI && *y_step < 0))
		*y_step *= -1;
	ray->next_vert_x = x_intercept;
	ray->next_vert_y = y_intercept;
}

void	check_vertical_hit(t_game *game, t_ray *ray,
				int facing_left)
{
	float	x_step;
	float	y_step;
	int		check_x;
	int		hit_type;

	prepare_vertical_check(game, ray, &x_step, &y_step);
	while (ray->next_vert_x >= 0 && \
		ray->next_vert_x <= game->parse_data.width * TILESIZE && \
		ray->next_vert_y >= 0 && \
		ray->next_vert_y <= game->parse_data.height * TILESIZE)
	{
		if (facing_left)
			check_x = ray->next_vert_x - 1;
		else
			check_x = ray->next_vert_x;
		hit_type = has_wall_at(check_x, ray->next_vert_y, game);
		if (hit_type == 1)
		{
			ray->found_vert_hit = 1;
			ray->vert_hit_x = ray->next_vert_x;
			ray->vert_hit_y = ray->next_vert_y;
			ray->vert_hit_is_door = 0;
			return ;
		}
		ray->next_vert_x += x_step;
		ray->next_vert_y += y_step;
	}
}

void	set_closest_hit(t_ray *ray, float horz_dist, float vert_dist)
{
	if (vert_dist < horz_dist)
	{
		ray->wall_hit_x = ray->vert_hit_x;
		ray->wall_hit_y = ray->vert_hit_y;
		ray->distance = vert_dist;
		ray->was_hit_vertical = 1;
	}
	else
	{
		ray->wall_hit_x = ray->horz_hit_x;
		ray->wall_hit_y = ray->horz_hit_y;
		ray->distance = horz_dist;
		ray->was_hit_vertical = 0;
	}
}
