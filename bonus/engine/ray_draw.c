/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:04:18 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/13 16:22:11 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_cardinals	*choose_texture(t_game *game, t_ray *ray)
{
	if (ray->was_hit_vertical)
	{
		if (ray->ray_angle < M_PI_2 || ray->ray_angle > 3 * M_PI_2)
			return (&game->parse_data.ea);
		else
			return (&game->parse_data.we);
	}
	else
	{
		if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
			return (&game->parse_data.so);
		else
			return (&game->parse_data.no);
	}
}

int	get_texture_x(t_ray *ray)
{
	int		tex_x;

	if (ray->was_hit_vertical)
	{
		tex_x = (int)ray->wall_hit_y % TILESIZE;
		if (ray->ray_angle > M_PI_2 && ray->ray_angle < 3 * M_PI_2)
			tex_x = TILESIZE - tex_x - 1;
	}
	else
	{
		tex_x = (int)ray->wall_hit_x % TILESIZE;
		if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
			tex_x = TILESIZE - tex_x - 1;
	}
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TILESIZE)
		tex_x = TILESIZE - 1;
	return (tex_x);
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

unsigned int	shade_color(unsigned int color, float distance, t_game *game)
{
	float			shade_factor;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	// !ahm ahm
	//? Light intensity = 1 / (1 + k * distance) Where k is a constant
	if (game->light % 2 == 0)
		shade_factor = 1.0f / (1.0f + distance * 0.001f);
	else
		shade_factor = 1.0f / (1.0f + distance * 0.03f);
	
	r = ((color >> 16) & 0xFF) * shade_factor;
	g = ((color >> 8) & 0xFF) * shade_factor;
	b = (color & 0xFF) * shade_factor;
	return ((r << 16) | (g << 8) | b);
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
		put_pixel_in_img(game, p->x + p->i, y, shade_color(color, game->ray.distance, game));
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
