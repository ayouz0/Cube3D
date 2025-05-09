/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:46:53 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/08 16:56:50 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing(int ac, char **av, t_game *game)
{
	(void)game;
	if (ac != 2)
		return (printf("Error: usage: ./cub3d <filename>.cub\n"), 1);
	if (ft_strlen(av[1]) < 4 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		return (printf("Error: bad file extention\n"), 1);
	game->parse_data.c = -1;
	game->parse_data.f = -1;
	game->parse_data.NO.ptr = 0x0;
	game->parse_data.SO.ptr = 0x0;
	game->parse_data.WE.ptr = 0x0;
	game->parse_data.EA.ptr = 0x0;
	if (load_cardinals_and_colors(game, av) != 0)
		return (free_parse_data(game), 1);
	if (load_map(game))
		return (1);
	return(0);
}
