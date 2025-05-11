/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:04:18 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/11 20:05:42 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_cardinals	*choose_texture(t_game *game, t_ray *ray)
{
	if (ray->was_hit_vertical)
	{
		if (ray->ray_angle < M_PI_2 || ray->ray_angle > 3 * M_PI_2)
			return (&game->parse_data.EA);
		else
			return (&game->parse_data.WE);
	}
	else
	{
		if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
			return (&game->parse_data.SO);
		else
			return (&game->parse_data.NO);
	}
}

int	get_texture_x(t_ray *ray)
{
	if (ray->was_hit_vertical)
		return ((int)ray->wall_hit_y % TILESIZE);
	return ((int)ray->wall_hit_x % TILESIZE);
}

int	get_texture_y(t_cardinals *tex, int height, int y)
{
	int	offset;
	int	tex_y;

	offset = y + (height / 2) - (WINDOW_HEIGHT / 2);
	tex_y = (offset * tex->h) / height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->h)
		tex_y = tex->h - 1;
	return (tex_y);
}

void	draw_column_strip(t_game *game, t_column_params *p, int height)
{
	int		y;
	int		tex_y;
	char	*pix;
	int		color;

	y = p->top;
	while (y < p->bottom)
	{
		tex_y = get_texture_y(p->texture, height, y);
		pix = p->texture->addr + (tex_y * p->texture->line_length + \
				p->tex_x * (p->texture->bits_per_pixel / 8));
		color = *(unsigned int *)pix;
		put_pixel_in_img(game, p->x + p->i, y, color);
		y++;
	}
}

void	draw_textured_column(t_game *game, t_ray *ray, int ray_id, int height)
{
	t_column_params	params;

	params.x = ray_id * RES;
	params.tex_x = get_texture_x(ray);
	params.texture = choose_texture(game, ray);
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
