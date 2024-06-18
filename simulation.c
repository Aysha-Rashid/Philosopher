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

void	eat(t_philo *philo, t_data *data)
{
	if (!philo->every_die)
	{
		// if (philo->current_philo % 2 == 0)
		// 	usleep(1000);
		pthread_mutex_lock(philo->right_fork);
		print_action(data, philo->current_philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork);
		print_action(data, philo->current_philo, "has taken a fork");
		pthread_mutex_lock(&data->death_check);
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&data->death_check);
		print_action(data, philo->current_philo, "is eating");
		ft_sleep(philo->time_to_eat);
		if (philo->no_of_meal > 0)
			philo->no_of_meal--;
		if (philo->no_of_meal == 0)
			philo->meal_finish = 1;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->total_philo == 1)
		return (handle_one(philo->data), NULL);
	if (philo->current_philo % 2 == 0)
		ft_sleep(philo->time_to_eat - 10);
	while (!philo->every_die && philo->no_of_meal)
	{
		if (!philo->every_die)
		{
			eat(philo, philo->data);
			if (philo->every_die || !philo->no_of_meal)
				return (NULL);
			if (!philo->every_die)
				print_action(philo->data, philo->current_philo, "is sleeping");
			if (!philo->every_die)
				ft_sleep(philo->time_to_sleep);
			if (!philo->every_die)
				print_action(philo->data, philo->current_philo, "is thinking");
		}
	}
	return (NULL);
}

int	check_philosopher(t_data *data, int i)
{
	pthread_mutex_lock(&data->resources[i].philo_dead);
	if ((get_current_time() - data->resources[i].last_meal_time)
		>= data->resources[i].time_to_die)
	{
		print_action(data, data->resources[i].current_philo, "died");
		every_die(data);
		data->dead_flag = 1;
	}
	pthread_mutex_unlock(&data->resources[i].philo_dead);
	return (data->dead_flag);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->dead_flag)
	{
		i = -1;
		while (++i < data->total_philo && !data->dead_flag)
		{
			if (!data->resources[i].no_of_meal)
				return (NULL);
			if (check_philosopher(data, i))
				return (NULL);
		}
		usleep(350);
	}
	return (NULL);
}

void	*simulation(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = -1;
	data->time = get_current_time();
	while (++i < data->total_philo && !data->dead_flag)
	{
		if (pthread_create(&data->resources[i].thread, NULL,
				routine, &data->resources[i]) != 0)
			return (printf("pthread_create() error"), NULL);
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
		return (printf("pthread_create() error"), NULL);
	if (data->dead_flag)
		return (NULL);
	i = -1;
	while (++i < data->total_philo)
	{
		if (pthread_join(data->resources[i].thread, NULL) != 0)
			return (printf("pthread_join() error"), NULL);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (printf("pthread_join() error"), NULL);
	return (NULL);
}
