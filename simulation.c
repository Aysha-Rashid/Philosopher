/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:56:20 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/06/01 20:20:57 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

//void  time_to_eat
//void  time_to_sleep
//void  time_to_think

// void	simulation_message(int time, char *message, int id)
// {
	
// }

// int	check_fork_and_eat(pthread_mutex_t	*fork)
// {
// 	if (fork)
// 	{
// 		pthread_mutex_lock(fork);
// 		return (1);
// 	}
// 	return (0);
// }

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	printf("%zu %d %s\n", get_current_time() - philo->data->time,
		philo->current_philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork);
	printf("%zu %d %s\n", get_current_time() - philo->data->time,
		philo->current_philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->death_check);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->death_check);
	printf("%zu %d %s\n", get_current_time() - philo->data->time,
		philo->current_philo, "is eating");
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->dead_flag)
	{
		eat(philo);
		philo->time_to_die = get_current_time() + philo->data->time;
		printf("%zu %d %s\n", get_current_time() - philo->data->time,
			philo->current_philo, "is sleeping");
		printf("%zu %d %s\n", get_current_time() - philo->data->time,
			philo->current_philo, "is thinking");
		if ((get_current_time() - philo->data->time) > philo->data->resources->time_to_die)
		{
			printf("%zu %d %s\n", get_current_time() - philo->data->time,
				philo->data->resources->current_philo, "died");
			philo->data->dead_flag = 1;
		}
		ft_sleep(philo->time_to_sleep);
		if (philo->no_of_meal > 0)
			philo->no_of_meal--;
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
		for (i = 0; i < data->total_philo && !data->dead_flag; i++)
		{
			pthread_mutex_lock(&data->death_check);
				// write(1, "come here", 9);
			if ((get_current_time() - data->time) > data->resources[i].time_to_die)
			{
				printf("%zu %d %s\n", get_current_time() - data->time,
					data->resources[i].current_philo, "died");
				data->dead_flag = 1;
			}
			pthread_mutex_unlock(&data->death_check);
		}
		usleep(1000);
	}
	return (NULL);
}

void	simulation(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = -1;
	data->time = get_current_time();
	if (data->total_philo == 1)
	{
		pthread_mutex_lock(&data->resources->left_fork);
		printf("%zu %d %s\n", get_current_time() - data->time,
			data->resources->current_philo, "has taken a fork");
		printf("%zu %d %s\n", data->resources->time_to_die,
			data->resources->current_philo, "died");
		return ;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
		(perror("pthread_create() error"), exit(EXIT_FAILURE));
	while (++i < data->total_philo)
	{
		if (pthread_create(&data->resources[i].thread,
				NULL, routine, &data->resources[i]) != 0)
			(perror("pthread_create() error"), exit(EXIT_FAILURE));
	}
	i = -1;
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
		(perror("pthread_create() error"), exit(EXIT_FAILURE));
	while (++i < data->total_philo)
	{
		if (pthread_join(data->resources[i].thread, NULL) != 0)
			(perror("pthread_join() error"), exit(EXIT_FAILURE));
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		(perror("pthread_join() error"), exit(EXIT_FAILURE));
}
