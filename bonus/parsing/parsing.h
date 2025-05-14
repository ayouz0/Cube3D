/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:47:57 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/14 12:43:07 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include "../engine/engine.h"
# include "../utils/utils.h"

typedef struct s_map_ctx
{
	char	**map;
	int		rows;
	int		cols;
}	t_map_ctx;

# define CEILING       "Error: Invalid ceiling color: %s\n"
# define FLOOR         "Error: Invalid floor color: %s\n"
# define CARDINALS     "Error: couldn't load all cardinals/colors\n"
# define CARDIN_COL    "Error: couldn't load all cardinals/colors\n"
# define OPEN_FAILURE  "Error: failed to open the file \"%s\"\n"
# define INVALID_LINE  "Error: invalid line while parsing cardinals/colors:\n%s"
# define DUPLICATE     "Error: found duplicate config info\n"
# define IMAGE_FAILURE "Error: failed to load an image\n"
# define INVALID_CONFG "Error: Invalid config line: %s\n"

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
int		check_invalid_characters(char **map, t_game *game);
int		validate_map(char **map, int rows, int cols, t_game *game);
int		space_neigh(char c);
void	increment_player_count(char c, long long *player_count);
int		check_top_bottom(char **map, int cols, int row);
int		check_side_borders(char **map, int rows, int cols);
int		is_player_char(char c);
int		is_map_cell(char c);
void	move_offset_to_map(char **line, int fd);
void	load_image_and_address(void	**img, t_game *game, \
		char *filename, t_cardinals *cardinal);
void	load_images(char **split, t_game *game, void **img);
#endif
