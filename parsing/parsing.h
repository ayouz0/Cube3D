/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:47:57 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/06 22:05:39 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#define IS_WALKABLE(c) ((c) == '0' || (c) == 'N' || (c) == 'S' || (c) == 'E' || (c) == 'W')
#define IS_SPACE(c) ((c) == ' ')
#define IS_WALL(c) ((c) == '1')

#include <fcntl.h>
// #include "../header.h"
#include "../engine/engine.h"
#include "../libft/libft.h"

int	parsing(int ac, char **av, t_game *game);

#endif
