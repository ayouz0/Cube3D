/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:47:57 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/08 15:58:04 by aaitabde         ###   ########.fr       */
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

int     parsing(int ac, char **av, t_game *game);
int     load_cardinals_and_colors(t_game *game, char **av);
int     load_map(t_game *game);
void    free_parse_data(t_game *game);
void	trim_endl(char **split);
int     parse_rgb(char *str, int *out_color);
void	free_2d(char **arr);
int     is_cardinal(char *line);
int     is_color(char *line);
void	free_map(char **map, int rows);

#endif
