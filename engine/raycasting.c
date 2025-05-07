/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:22:44 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/07 14:46:16 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

float distance_between_points(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void cast_single_ray(t_game *game, t_ray *ray)
{
	ray->ray_angle = normalize_angle(ray->ray_angle);

	int facing_down = (ray->ray_angle > 0 && ray->ray_angle < M_PI);
	int facing_up = !facing_down;
	int facing_right = (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI);
	int facing_left = !facing_right;

	float x_intercept, y_intercept;
	float x_step, y_step;

	/////////////////////////
	// HORIZONTAL HIT CHECK //
	/////////////////////////

	int found_horz_wall_hit = 0;
	float horz_wall_hit_x = 0;
	float horz_wall_hit_y = 0;

	y_intercept = floor(game->player.player_y / TILESIZE) * TILESIZE;
	y_intercept += facing_down ? TILESIZE : 0;

	x_intercept = game->player.player_x + (y_intercept - game->player.player_y) / tan(ray->ray_angle);

	y_step = TILESIZE;
	y_step *= facing_up ? -1 : 1;

	x_step = TILESIZE / tan(ray->ray_angle);
	if ((facing_left && x_step > 0) || (facing_right && x_step < 0))
		x_step *= -1;

	float next_horz_x = x_intercept;
	float next_horz_y = y_intercept;

	while (next_horz_x >= 0 && next_horz_x <= game->parse_data.width * TILESIZE &&
	   next_horz_y >= 0 && next_horz_y <= game->parse_data.height * TILESIZE)

	{
		int check_y = facing_up ? next_horz_y - 1 : next_horz_y;
		if (has_wall_at(next_horz_x, check_y, game->map))
		{
			found_horz_wall_hit = 1;
			horz_wall_hit_x = next_horz_x;
			horz_wall_hit_y = next_horz_y;
			break;
		}
		next_horz_x += x_step;
		next_horz_y += y_step;
	}

	/////////////////////////
	// VERTICAL HIT CHECK //
	/////////////////////////

	int found_vert_wall_hit = 0;
	float vert_wall_hit_x = 0;
	float vert_wall_hit_y = 0;

	x_intercept = floor(game->player.player_x / TILESIZE) * TILESIZE;
	x_intercept += facing_right ? TILESIZE : 0;

	y_intercept = game->player.player_y + (x_intercept - game->player.player_x) * tan(ray->ray_angle);

	x_step = TILESIZE;
	x_step *= facing_left ? -1 : 1;

	y_step = TILESIZE * tan(ray->ray_angle);
	if ((facing_up && y_step > 0) || (facing_down && y_step < 0))
		y_step *= -1;

	float next_vert_x = x_intercept;
	float next_vert_y = y_intercept;

	while (next_vert_x >= 0 && next_vert_x <= game->parse_data.width * TILESIZE &&
	   next_vert_y >= 0 && next_vert_y <= game->parse_data.height * TILESIZE)

	{
		int check_x = facing_left ? next_vert_x - 1 : next_vert_x;
		if (has_wall_at(check_x, next_vert_y, game->map))
		{
			found_vert_wall_hit = 1;
			vert_wall_hit_x = next_vert_x;
			vert_wall_hit_y = next_vert_y;
			break;
		}
		next_vert_x += x_step;
		next_vert_y += y_step;
	}

	/////////////////////////
	// CHOOSE CLOSER HIT //
	/////////////////////////

	float horz_hit_distance = found_horz_wall_hit
		? distance_between_points(game->player.player_x, game->player.player_y, horz_wall_hit_x, horz_wall_hit_y)
		: INFINITY;

	float vert_hit_distance = found_vert_wall_hit
		? distance_between_points(game->player.player_x, game->player.player_y, vert_wall_hit_x, vert_wall_hit_y)
		: INFINITY;

	if (vert_hit_distance < horz_hit_distance)
	{
		ray->wall_hit_x = vert_wall_hit_x;
		ray->wall_hit_y = vert_wall_hit_y;
		ray->distance = vert_hit_distance;
		ray->was_hit_vertical = 1;
	}
	else
	{
		ray->wall_hit_x = horz_wall_hit_x;
		ray->wall_hit_y = horz_wall_hit_y;
		ray->distance = horz_hit_distance;
		ray->was_hit_vertical = 0;
	}
}

unsigned int	shade_color(unsigned int color, float distance)
{
	float			shade_factor;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	// !ahm ahm
	//? Light intensity = 1 / (1 + k * distance) Where k is a constant
	shade_factor = 1.0f / (1.0f + distance * 0.01f);
	r = ((color >> 16) & 0xFF) * shade_factor;
	g = ((color >> 8) & 0xFF) * shade_factor;
	b = (color & 0xFF) * shade_factor;
	return ((r << 16) | (g << 8) | b);
}

void cast_all_rays(t_game *game, t_ray *ray)
{
	float ray_angle;
	int ray_id;

	ray_angle = game->player.mv.player_angle - (FOV / 2); // Start on the left side of the FOV
	ray_id = 0;
	while (ray_id < NUM_RAYS)
	{
		ray->ray_angle = ray_angle;

		// Cast one ray
		cast_single_ray(game, ray);

		// Correct the fish-eye effect
		float corrected_distance = ray->distance * cos(ray->ray_angle - game->player.mv.player_angle);

		// Calculate wall height based on corrected distance
		float distance_to_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
		int wall_strip_height = (TILESIZE / corrected_distance) * distance_to_proj_plane;

		// Calculate start and end pixel positions for the wall
		int wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		int wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);

		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		if (wall_bottom_pixel > WINDOW_HEIGHT)
			wall_bottom_pixel = WINDOW_HEIGHT;

		// Draw the vertical wall stripe
		int x = ray_id * RES;
		int i = 0;
		while (i < RES)
		{  
			int y = wall_top_pixel;
			while (y < wall_bottom_pixel)
			{
				put_pixel_in_img(game, x + i, y, shade_color(0xFFFFFF, ray->distance)); // gray wall color
				y++;
			}
			i++;
		}
		ray_angle += FOV / NUM_RAYS; // Rotate slightly for next ray
		ray_id++;
	}
}
