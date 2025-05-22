/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:14:21 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/22 10:18:02 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	is_valid_door(char **map, int y, int x)
{
	if (x == 0 || y == 0 || !map[y][x + 1] || !map[y + 1])
		return (0);
	if (map[y][x + 1] == '1' && map[y][x - 1] == '1' \
	&& map[y + 1][x] == '0' && map[y - 1][x] == '0')
		return (0);
	printf(DOORS_ERROR);
	return (1);
}
