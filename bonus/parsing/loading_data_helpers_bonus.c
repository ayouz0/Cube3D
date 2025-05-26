/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_data_helpers_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:13:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/26 13:48:51 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	load_image_and_address(void	**img, t_game *game, \
char *filename, t_cardinals *cardinal)
{
	*img = mlx_xpm_file_to_image(game->mlx, filename, &cardinal->w, \
	&cardinal->h);
	if (!(*img))
		return (printf("Error: image failed to load :\n%s\n", filename), 1);
	cardinal->ptr = *img;
	cardinal->addr = mlx_get_data_addr(cardinal->ptr, \
	&cardinal->bits_per_pixel, &cardinal->line_length, \
	&cardinal->endian);
	if (!cardinal->addr)
		return (1);
	return (0);
}

int	load_images(char **split, t_game *game, void **img)
{
	if (ft_strncmp(split[0], "NO", 3) == 0)
		return (load_image_and_address(img, game, \
		split[1], &game->parse_data.no));
	else if (ft_strncmp(split[0], "SO", 3) == 0)
		return (load_image_and_address(img, game, \
		split[1], &game->parse_data.so));
	else if (ft_strncmp(split[0], "WE", 3) == 0)
		return (load_image_and_address(img, game, \
		split[1], &game->parse_data.we));
	else if (ft_strncmp(split[0], "EA", 3) == 0)
		return (load_image_and_address(img, game, \
		split[1], &game->parse_data.ea));
	return (0);
}
