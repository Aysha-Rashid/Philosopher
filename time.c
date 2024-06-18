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

void	ft_sleep(size_t milliseconds)
{
	size_t	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < (size_t)milliseconds)
		usleep(100);
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

void	handle_one(t_data	*data)
{
	pthread_mutex_lock(&data->resources->left_fork);
	print_action(data, 1, "has taken a fork");
	pthread_mutex_unlock(&data->resources->left_fork);
	pthread_mutex_lock(&data->resources->philo_dead);
	printf("%zu %d %s\n", data->resources->time_to_die,
		data->resources->current_philo, "died");
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->resources->philo_dead);
}
