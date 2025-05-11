/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:47:57 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/11 14:48:32 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include "../engine/engine.h"
# include "../libft/libft.h"

int		parsing(int ac, char **av, t_game *game);
int		load_cardinals_and_colors(t_game *game, char **av);
int		load_map(t_game *game);
void	free_parse_data(t_game *game);
void	trim_endl(char **split);
int		parse_rgb(char *str, int *out_color);
void	free_2d(char **arr);
int		is_cardinal(char *line);
int		is_color(char *line);
void	free_map(char **map, int rows);

#endif
