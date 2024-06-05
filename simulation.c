/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:56:20 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/06/05 16:34:20 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void *monitor(void *arg)
{
	t_data *data;
	int i;

	i = 0;
	data = (t_data *)arg;
	while (!data->dead_flag)
	{
		// if (data->resources[i].meal_finish == 1)
		// 	break ;
		pthread_mutex_lock(&data->death_check);
		for (i = 0; i < data->total_philo && !data->dead_flag; i++)
		{
			if ((get_current_time() - data->resources[i].last_meal_time) > data->resources[i].time_to_die)
			{
				printf("%zu %d %s\n", get_current_time() - data->time,
					   data->resources[i].current_philo, "died");
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->death_check);
				break ;
			}
		}
		pthread_mutex_unlock(&data->death_check);
		usleep(1000);
	}
	return NULL;
}

void eat(t_philo *philo, t_data *data)
{
	// if (data->dead_flag)
	// 	return ;
	if (!data->dead_flag)
	{
		if (philo->current_philo % 2 == 0)
		{
			pthread_mutex_lock(&philo->left_fork);
			printf("%zu %d %s\n", get_current_time() - data->time,
				   philo->current_philo, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			printf("%zu %d %s\n", get_current_time() - data->time,
				   philo->current_philo, "has taken a fork");
		}
		else
		{
			usleep(1000);
			pthread_mutex_lock(philo->right_fork);
			printf("%zu %d %s\n", get_current_time() - data->time,
				   philo->current_philo, "has taken a fork");
			pthread_mutex_lock(&philo->left_fork);
			printf("%zu %d %s\n", get_current_time() - data->time,
				   philo->current_philo, "has taken a fork");
		}
		pthread_mutex_lock(&data->death_check); // Lock death_check for updating last_meal_time
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&data->death_check); // Unlock death_check
		printf("%zu %d %s\n", get_current_time() - data->time,
			   philo->current_philo, "is eating");
		ft_sleep(philo->time_to_eat); // Simulate eating
		pthread_mutex_unlock(&philo->left_fork); // Unlock left fork after eating
		pthread_mutex_unlock(philo->right_fork); // Unlock right fork after eating
	}
}

// // time issues
// // mutex_lock and unlock for each philo
// // odd number of philo check
// // number of meals

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->data->time = get_current_time();
	while (!philo->data->dead_flag && !philo->meal_finish)
	{
		eat(philo, philo->data);
		if (philo->data->dead_flag)
			return NULL;
		if (philo->no_of_meal > 0)
		{
			philo->no_of_meal--;
			printf("current philo: %d no_of_meal: %d\n", philo->current_philo, philo->no_of_meal);
		}
		// if (philo->no_of_meal == 0)
		// 	philo->meal_finish = 1;
		printf("%zu %d %s\n", get_current_time() - philo->data->time,
			   philo->current_philo, "is sleeping");
		ft_sleep(philo->time_to_sleep); // Simulate thinking
		printf("%zu %d %s\n", get_current_time() - philo->data->time,
			   philo->current_philo, "is thinking");
		// if (philo->no_of_meal > 0)
		// 	philo->no_of_meal--;
	}
	return NULL;
}

void *simulation(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i  = -1;
	if (data->total_philo == 1)
	{
		pthread_mutex_lock(&data->resources->left_fork);
		printf("%zu %d %s\n", get_current_time() - data->time,
			   data->resources->current_philo, "has taken a fork");
	}
	data->time = get_current_time();
	while (++i < data->total_philo)
	{
		if (pthread_create(&data->resources[i].thread, NULL, routine, &data->resources[i]) != 0)
			return (perror("pthread_create() error"), NULL);
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
		return (perror("pthread_create() error"), NULL);
	i = -1;
	while (++i < data->total_philo)
	{
		if (pthread_join(data->resources[i].thread, NULL) != 0)
			return (perror("pthread_join() error"), NULL);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (perror("pthread_join() error"), NULL);
	return NULL;
}
