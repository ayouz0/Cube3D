/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:30:36 by aaitabde          #+#    #+#             */
/*   Updated: 2024/11/09 15:34:13 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	dv;
	unsigned char	*str;

	str = (unsigned char *)s;
	dv = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == dv)
			return ((unsigned char *)&str[i]);
		i++;
	}
	return (NULL);
}
