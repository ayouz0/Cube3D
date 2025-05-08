/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cardinals_and_colors.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:48:16 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/08 16:41:51 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_color(char *line)
{
	if (!line)
		return(1);
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (0);
	return(1);
}

/*only one expression would be true for the string comparisons
witch makes "found" a bool*/
int	is_cardinal(char *line)
{
	int found;

	found = 0;
	if (!line)
		return(1);
	found += (!ft_strncmp(line, "NO ", 3)) + (!ft_strncmp(line, "SO ", 3)) \
	+ (!ft_strncmp(line, "EA ", 3)) + (!ft_strncmp(line, "WE ", 3));
	return (!found);
}

int	parse_rgb(char *str, int *out_color)
{
	char	**tmp;
	int		r;
	int		g;
	int		b;

	tmp = ft_split(str, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
		return (free_2d(tmp), 1);
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	free_2d(tmp);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	*out_color = (r << 16) | (g << 8) | b;
	return (0);
}
