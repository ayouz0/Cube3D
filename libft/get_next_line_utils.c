/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:05:32 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/08 16:14:48 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int	check_new_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*fill_fix_line(char **buf, int len)
{
	int		i;
	char	*line;
	char	*tmp_buf;

	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = (*buf)[i];
		i++;
	}
	line[len] = '\n';
	line[len + 1] = '\0';
	tmp_buf = ft_strdup(&(*buf)[len + 1]);
	free(*buf);
	*buf = NULL;
	*buf = tmp_buf;
	return (line);
}