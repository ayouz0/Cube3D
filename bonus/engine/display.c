/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:58:29 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/17 20:59:01 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_in_img(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

t_cardinals	*choose_texture(t_game *game, t_ray *ray)
{
	if ((ray->was_hit_vertical && ray->vert_hit_is_door) || \
		(!ray->was_hit_vertical && ray->horz_hit_is_door))
		return (&game->door_tex);
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

unsigned int	shade_color(unsigned int color, float distance, t_game *game)
{
	float			shade_factor;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	if (game->light % 2 == 0)
		shade_factor = 1.0f / (1.0f + distance * 0.001f);
	else
		shade_factor = 1.0f / (1.0f + distance * 0.03f);
	r = ((color >> 16) & 0xFF) * shade_factor;
	g = ((color >> 8) & 0xFF) * shade_factor;
	b = (color & 0xFF) * shade_factor;
	return ((r << 16) | (g << 8) | b);
}
