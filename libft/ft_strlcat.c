/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:01:13 by aaitabde          #+#    #+#             */
/*   Updated: 2024/11/14 17:17:26 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	i;

	i = 0;
	if (dstsize <= 0 && !dst)
		return (ft_strlen(src));
	dlen = ft_strlen(dst);
	if (dstsize <= dlen)
		return (ft_strlen(src) + dstsize);
	while (src[i] != '\0' && i < dstsize - dlen - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + ft_strlen(src));
}
