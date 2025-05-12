/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:51:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/12 12:40:50 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_2d(char **arr)
{
	int	i;

	if (!arr)
		return ;
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
	int	i;
	int	len;

	i = 0;
	while (split[i])
	{
		len = ft_strlen(split[i]);
		if (len > 0 && split[i][len - 1] == '\n')
			split[i][len - 1] = '\0';
		i++;
	}
}

void	free_parse_data(t_game *game)
{
	if (game->parse_data.no.ptr)
		mlx_destroy_image(game->mlx, game->parse_data.no.ptr);
	if (game->parse_data.so.ptr)
		mlx_destroy_image(game->mlx, game->parse_data.so.ptr);
	if (game->parse_data.we.ptr)
		mlx_destroy_image(game->mlx, game->parse_data.we.ptr);
	if (game->parse_data.ea.ptr)
		mlx_destroy_image(game->mlx, game->parse_data.ea.ptr);
	game->parse_data.no.ptr = NULL;
	game->parse_data.so.ptr = NULL;
	game->parse_data.we.ptr = NULL;
	game->parse_data.ea.ptr = NULL;
}

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}
