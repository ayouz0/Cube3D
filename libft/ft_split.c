/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:28:09 by aaitabde          #+#    #+#             */
/*   Updated: 2024/11/08 20:41:32 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_counter(const char *s, char c)
{
	size_t	i;
	size_t	count;
	int		found;

	count = 0;
	found = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			found = 0;
		else if (found == 0)
		{
			count++;
			found = 1;
		}
		i++;
	}
	return (count);
}

static size_t	word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_allocateword(const char *s, char c, size_t *j)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (word_len(s, c) + 1));
	if (!str)
		return (NULL);
	while (i < word_len(s, c))
	{
		str[i] = s[i];
		i++;
	}
	*j += i;
	str[i] = '\0';
	return (str);
}

static void	ft_freer(char **strs, size_t words)
{
	size_t	i;

	i = 0;
	while (i < words)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**strs;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	strs = (char **)malloc((word_counter(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (0);
	while (i < word_counter(s, c))
	{
		while (s[j] == c)
			j++;
		strs[i] = ft_allocateword(&s[j], c, &j);
		if (!strs[i])
			return (ft_freer(strs, i), NULL);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
