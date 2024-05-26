/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:42:11 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/05/26 22:03:47 by ayal-ras         ###   ########.fr       */
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
