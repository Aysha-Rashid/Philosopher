/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:17:10 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/05/29 19:52:20 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_sleep(size_t	milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(milliseconds / 10);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if ((gettimeofday(&time, NULL)) == -1)
	{
		printf("gettimeofday error!\n");
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec/1000); // convert the number of seconds into milliseconds
	// convert the number of microseconds into milliseconds
}
