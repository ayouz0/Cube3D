/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:41:12 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/22 08:57:16 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	draw_light_sprite(t_game *game, t_cardinals *sprite, \
							int dest_x, int dest_y)
{
	int	x;
	int	y;
	int	color;
	int	src_offset;

	y = 0;
	while (y < sprite->h)
	{
		x = 0;
		while (x < sprite->w)
		{
			src_offset = y * sprite->line_length + \
							x * (sprite->bits_per_pixel / 8);
			color = *(int *)(sprite->addr + src_offset);
			if ((color & 0x00FFFFFF) != 0x000000)
				put_pixel_in_img(game, dest_x + x, dest_y + y, color);
			x++;
		}
		y++;
	}
}

void	animate_sprite(t_game *game)
{
	static long	last_update;
	static int	anim_frame;
	long		current_time;

	if (!game->light)
		return ;
	current_time = get_current_time_ms();
	if (current_time - last_update >= 100)
	{
		anim_frame += game->direction;
		if (anim_frame == 7 || anim_frame == 0)
			game->direction *= -1;
		last_update = current_time;
	}
	draw_light_sprite(game, &game->light_img[anim_frame], 14 * 48, 8 * 48);
}
