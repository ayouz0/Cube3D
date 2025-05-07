/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:05:30 by aaitabde          #+#    #+#             */
/*   Updated: 2024/11/15 20:26:37 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *ndl, size_t len)
{
	size_t	i;
	size_t	j;
	char	*h;

	i = 0;
	j = 0;
	if (!hay && len == 0 && ndl)
		return (NULL);
	h = (char *)hay;
	if (!ndl[0])
		return (h);
	while (h[i] != '\0' && i < len)
	{
		j = 0;
		while ((h[i + j] == ndl[j]) && (ndl[j]) && (h[i + j]) && (i + j) < len)
			j++;
		if (j == ft_strlen(ndl))
			return (&h[i]);
		i++;
	}
	return (NULL);
}
