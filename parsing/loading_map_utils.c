/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:51:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/08 15:52:27 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_2d(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


void	trim_endl(char **split)
{
	int i = 0;

	while (split[i])
	{
		int len = ft_strlen(split[i]);
		if (len > 0 && split[i][len - 1] == '\n')
			split[i][len - 1] = '\0';
		i++;
	}
}

void	free_parse_data(t_game *game)
{
	if (game->parse_data.NO.ptr)
		mlx_destroy_image(game->mlx, game->parse_data.NO.ptr);
	if (game->parse_data.SO.ptr)
		mlx_destroy_image(game->mlx, game->parse_data.SO.ptr);
	if (game->parse_data.WE.ptr)
		mlx_destroy_image(game->mlx, game->parse_data.WE.ptr);
	if (game->parse_data.EA.ptr)
		mlx_destroy_image(game->mlx, game->parse_data.EA.ptr);
	game->parse_data.NO.ptr = NULL;
	game->parse_data.SO.ptr = NULL;
	game->parse_data.WE.ptr = NULL;
	game->parse_data.EA.ptr = NULL;
}

void	free_map(char **map, int rows)
{
	int i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}
