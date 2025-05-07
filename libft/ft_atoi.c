/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:08:37 by aaitabde          #+#    #+#             */
/*   Updated: 2024/11/08 22:40:32 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	nums(int *i, long long *result, int *isng)
{
	*i = 0;
	*result = 0;
	*isng = 1;
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	int			isng;

	nums(&i, &result, &isng);
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			isng *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (LLONG_MAX / 10)
			|| (result == (LLONG_MAX / 10) && str[i] - '0' > LLONG_MAX % 10))
		{
			if (isng == -1)
				return (0);
			else
				return (-1);
		}
		result = (result * 10) + (str[i++] - '0');
	}
	return (result * isng);
}
