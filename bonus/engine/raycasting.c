/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:22:44 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/15 21:00:55 by hfhad            ###   ########.fr       */
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

int get_door_texture_x(t_ray *ray) 
{
    int tex_x = (int)ray->door.x % TILESIZE;
    if (ray->door.facing_up)  // Facing up, hitting south side
        tex_x = TILESIZE - tex_x - 1;
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= TILESIZE)
        tex_x = TILESIZE - 1;
    return tex_x;
}
int get_door_texture_y(t_cardinals *tex, int height, int y, int unclipped_top)
{
    int offset = y - unclipped_top;  // Position relative to the unclipped top
    int tex_y = (offset * tex->h) / height;
    if (tex_y < 0)
        tex_y = 0;
    if (tex_y >= tex->h)
        tex_y = tex->h - 1;
    return tex_y;
}

void draw_door_column_strip(t_game *game, t_column_params *p, int height, int is_door)
{
	(void) is_door;
    int y = p->top;
    while (y < p->bottom)
    {
        // Update get_texture_y to use unclipped_top
        int tex_y = get_door_texture_y(p->texture, height, y, p->unclipped_top);
        char *pix = p->texture->addr + (tex_y * p->texture->line_length + 
                                        p->tex_x * (p->texture->bits_per_pixel / 8));
        int color = *(unsigned int *)pix;
        // Use p->distance instead of game->ray.distance for shading
        put_pixel_in_img(game, p->x + p->i, y, shade_color(color, p->distance, game));
        y++;
    }
}

void draw_door_column(t_game *game, t_ray *ray, int ray_id, int height, float door_dist)
{
    t_column_params params;
    params.x = ray_id * RES;
    params.tex_x = get_door_texture_x(ray);
    params.texture = &game->door_tex;

    // Adjusted parameters for smoother sliding
    float max_offset = 800.0f;          // Reduced from 850
    float threshold_distance = 350.0f;  // Reduced from 350
    
    // Calculate offset using ACTUAL distance
    float offset = max_offset * (1.0f - fminf(door_dist / threshold_distance, 1.0f));

    int center = WINDOW_HEIGHT / 2;
    int unclipped_top = center - (height / 2) - (int)offset;
    
    // Clip to screen bounds
    params.top = (unclipped_top < 0) ? 0 : unclipped_top;
    params.bottom = center + (height / 2) - (int)offset;
    if (params.bottom > WINDOW_HEIGHT) params.bottom = WINDOW_HEIGHT;

    params.unclipped_top = unclipped_top;
    params.distance = door_dist;

    params.i = 0;
    while (params.i < RES)
    {
        draw_door_column_strip(game, &params, height, 1);
        params.i++;
    }
}

void	render_wall_slice(t_game *game, t_ray *ray, int ray_id)
{
	int		wall_height;
	float	corrected_dist;
	float	proj_plane_dist;
	float	actual_dist;
	corrected_dist = ray->distance * \
		cos(ray->ray_angle - game->player.mv.player_angle);
	proj_plane_dist = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	wall_height = (TILESIZE / corrected_dist) * proj_plane_dist;
	draw_textured_column(game, ray, ray_id, wall_height);
			printf("%d  \n", ray->door.door_num);
			
	// printf("point     %d  %d  %d  %d\n", ray->door.y, ray->door.x, ray->door.dx , ray->door.dy);
	while (ray->door.door_num > 0)
	{
		if ( ray->door.y / TILESIZE  >= 0 &&  ray->door.x / TILESIZE >=0 && game->map[(int)(ray->door.y / TILESIZE)][(int)(ray->door.x / TILESIZE)] == 'D')
		{
			actual_dist = distance_between_points(ray->door.x, ray->door.y, game->player.player_x, game->player.player_y);
			corrected_dist = actual_dist * \
			cos(ray->ray_angle - game->player.mv.player_angle);
			proj_plane_dist = (WINDOW_WIDTH / 2) / tan(FOV / 2);
			wall_height = (TILESIZE / corrected_dist) * proj_plane_dist;
			draw_door_column(game, ray, ray_id, wall_height, corrected_dist);
			ray->door.door_num--;
		}
		ray->door.y += ray->door.dy;
		ray->door.x += ray->door.dx;
	}
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
		ray->door.door_num = 0;
        ray->vert_hit_is_door = 0;
        ray->horz_hit_is_door = 0;
		cast_single_ray(game, ray);
		render_wall_slice(game, ray, ray_id);
		ray_angle += FOV / NUM_RAYS;
		ray_id++;
	
	}
}
