/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:42:11 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/05/30 19:28:12 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char	*str1, char	*str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if ((char)str1[i] != (char)str2[i])
			return ((char)str1[i] - (char)str2[i]);
		i++;
	}
	return ((char)str1[i] - (char)str2[i]);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	overflow(long max, long r, int sign)
{
	if (r >= (max / 10))
	{
		if (sign == 1)
			return (-1);
		if (sign == -1)
			return (0);
	}
	return (r);
}

int	ft_atoi(const char	*str)
{
	long	r;
	int		sign;
	int		i;
	long	max;

	max = 9223372036854775807;
	i = 0;
	sign = 1;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		overflow(max, r, sign);
		r = (r * 10) + str[i++] - '0';
	}
	return ((int)r * sign);
}
