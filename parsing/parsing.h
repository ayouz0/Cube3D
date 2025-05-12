/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:47:57 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/12 11:34:31 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include "../engine/engine.h"
# include "../libft/libft.h"

typedef struct s_map_ctx
{
	char	**map;
	int		rows;
	int		cols;
}	t_map_ctx;

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
int		check_invalid_characters(char **map);
int		validate_map(char **map, int rows, int cols);
int		space_neigh(char c);
void	increment_player_count(char c, long long *player_count);
int		check_top_bottom(char **map, int cols, int row);
int		check_side_borders(char **map, int rows, int cols);
int		is_player_char(char c);
int		is_map_cell(char c);

#endif
