/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:02:19 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/23 12:57:59 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

# define ORANGE1    "\033[38;2;255;100;0m"
# define ORANGE2    "\033[38;2;255;150;0m"
# define ORANGE3    "\033[38;2;255;200;0m"
# define ORANGE4    "\033[38;2;255;150;0m"
# define ORANGE5    "\033[38;2;255;50;0m"
# define TITLE_CLR  "\033[1m\033[38;2;255;200;0m"
# define GREEN      "\033[38;2;0;255;100m"
# define BLUE       "\033[38;2;100;200;255m"
# define YELLOW     "\033[38;2;255;255;100m"
# define PURPLE     "\033[38;2;255;100;255m"
# define BOLD       "\033[1m"
# define RESET      "\033[0m"

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "engine/engine_bonus.h"
# include "parsing/parsing_bonus.h"
# include "minimap_bonus/minimap_bonus.h"

void	init_logic(t_game *game);
int		init_door(t_game *game);
int		init_light(t_game *game);
#endif