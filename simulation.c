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

#include "philo.h"

void	print_action(t_data	*data, int id, char *message)
{
	pthread_mutex_lock(&data->write);
	if (!data->dead_flag)
		printf("%zu %d %s\n", get_current_time()
			- data->time, id, message);
	pthread_mutex_unlock(&data->write);
}


void eat(t_philo *philo, t_data *data)
{
	if (data->dead_flag || data->total_philo == 1)
		return;
	if (philo->current_philo % 2 == 0)
		usleep(1000);
	if (data->dead_flag || data->total_philo == 1)
		return;
	pthread_mutex_lock(philo->right_fork);
	print_action(data, philo->current_philo, "has taken a fork");
	if (data->dead_flag)
		return ;
	pthread_mutex_lock(&philo->left_fork);
	print_action(data, philo->current_philo, "has taken a fork");
	if (data->dead_flag)
		return ;
	pthread_mutex_lock(&data->death_check);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&data->death_check);
	if (!data->dead_flag)
	{
		print_action(data, philo->current_philo, "is eating");
		ft_sleep(philo->time_to_eat);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (!philo->data->dead_flag && !philo->meal_finish)
	{
		if (philo->data->dead_flag)
			return (NULL);
		eat(philo, philo->data);
		if (philo->data->dead_flag)
			return (NULL);
		if (philo->no_of_meal > 0)
			philo->no_of_meal--;
		if (philo->data->dead_flag)
			return (NULL);
		print_action(philo->data, philo->current_philo, "is sleeping");
		if (philo->data->dead_flag)
			return (NULL);
		ft_sleep(philo->time_to_sleep);
		if (philo->data->dead_flag)
			return (NULL);
		print_action(philo->data, philo->current_philo, "is thinking");
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (!data->dead_flag)
	{
		for (i = 0; i < data->total_philo; i++)
		{
			pthread_mutex_lock(&data->resources[i].philo_dead);
			if ((get_current_time() - data->resources[i].last_meal_time) >= data->resources[i].time_to_die)
			{
				print_action(data, data->resources[i].current_philo, "died");
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->resources[i].philo_dead);
				return (NULL);
			}
			pthread_mutex_unlock(&data->resources[i].philo_dead);
		}
		usleep(1000); // was 50
	}
	return (NULL);
}

void *simulation(t_data *data) {
	pthread_t monitor_thread;
	int i;

	data->time = get_current_time();
	// data->resources->all_died = 0;
	if (data->total_philo == 1) {
		pthread_mutex_lock(&data->resources->left_fork);
		print_action(data, 1, "has taken a fork");
		pthread_mutex_unlock(&data->resources->left_fork);
		// return (NULL);
	}
	for (i = 0; i < data->total_philo && data->total_philo != 1; i++) {
		if (pthread_create(&data->resources[i].thread, NULL, routine, &data->resources[i]) != 0) {
			perror("pthread_create() error");
			return (NULL);
		}
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0) {
		perror("pthread_create() error");
		return (NULL);
	}
	for (i = 0; i < data->total_philo && data->total_philo != 1; i++) {
		if (pthread_join(data->resources[i].thread, NULL) != 0) {
			perror("pthread_join() error");
			return (NULL);
		}
	}
	if (pthread_join(monitor_thread, NULL) != 0) {
		perror("pthread_join() error");
		return (NULL);
	}
	return (NULL);
}
