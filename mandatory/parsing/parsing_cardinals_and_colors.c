/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cardinals_and_colors.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:48:16 by aaitabde          #+#    #+#             */
/*   Updated: 2025/05/30 16:01:33 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_color(char *line)
{
	if (!line)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (0);
	return (1);
}

/*only one expression would be true for the string comparisons
witch makes "found" a bool*/
int	is_cardinal(char *line)
{
	int	found;

	found = 0;
	if (!line)
		return (1);
	found += (!ft_strncmp(line, "NO ", 3)) + (!ft_strncmp(line, "SO ", 3)) \
	+ (!ft_strncmp(line, "EA ", 3)) + (!ft_strncmp(line, "WE ", 3));
	return (!found);
}

static int	read_component(char *str, int *i, int *value)
{
	int	n;
	int	count;

	n = 0;
	count = 0;
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (n > 255)
			return (1);
		n = n * 10 + (str[*i] - '0');
		(*i)++;
		count++;
	}
	while (str[*i] == ' ')
		(*i)++;
	if (count == 0 || n > 255)
		return (1);
	*value = n;
	return (0);
}

int	parse_rgb(char *str, int *out_color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (read_component(str, &i, &r))
		return (1);
	if (str[i++] != ',')
		return (1);
	if (read_component(str, &i, &g))
		return (1);
	if (str[i] != ',')
		return (1);
	i++;
	if (read_component(str, &i, &b))
		return (1);
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (1);
	*out_color = (r << 16) | (g << 8) | b;
	return (0);
}
