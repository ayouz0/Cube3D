/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:02:19 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/22 09:45:14 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "engine/engine_bonus.h"
# include "parsing/parsing.h"
# include "minimap_bonus/minimap_bonus.h"

void	init_logic(t_game *game);
int		init_door(t_game *game);
int		init_light(t_game *game);
#endif