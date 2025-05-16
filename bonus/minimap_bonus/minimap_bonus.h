/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:10:31 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/16 11:54:34 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H
#include "../header.h"

void	init_minimap(t_game *game);
int		render_minimap(void *game_);
void	draw_cardinals_on_minimap(t_game *game);


# define MINIMAP_PAD 6
# define BORDER_THICKNESS 4
# define LINE_LENGHT 20

#endif