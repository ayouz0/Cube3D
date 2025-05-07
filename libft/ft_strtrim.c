/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:08:16 by aaitabde          #+#    #+#             */
/*   Updated: 2024/11/08 20:24:19 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(const char s, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0' && s != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	start;
	char	*s;

	if (!s1)
		return (NULL);
	if (!set || ft_strlen(set) == 0 || ft_strlen(s1) == 0)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1) - 1;
	start = 0;
	while (s1[start] != '\0' && (char_in_set(s1[start], set) == 1))
		start++;
	while (j > start && (char_in_set(s1[j], set)) == 1)
		j--;
	s = (char *)malloc(sizeof(char) * (j - start + 2));
	if (!s)
		return (NULL);
	while (start <= j)
		s[i++] = s1[start++];
	s[i] = '\0';
	return (s);
}
