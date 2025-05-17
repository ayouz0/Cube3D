/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:12:37 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/17 21:13:49 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

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
