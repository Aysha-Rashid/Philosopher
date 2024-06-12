/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:17:10 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/05/31 20:20:03 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void ft_sleep(size_t milliseconds)
// {
// 	// size_t	time;

// 	// time = get_current_time();
// 	// if (get_current_time() - time > milliseconds)
// 		usleep(1000 * milliseconds);
// }

void ft_sleep(size_t milliseconds) {
    size_t start_time = get_current_time();
    while ((get_current_time() - start_time) < (size_t)milliseconds) {
        usleep(100); // sleep for 100 microseconds to avoid busy-waiting
    }
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if ((gettimeofday(&time, NULL)) == -1)
	{
		printf("gettimeofday error!\n");
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
