/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:56:20 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/05/31 21:25:47 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

//void  time_to_eat
//void  time_to_sleep
//void  time_to_think

// void	simulation_message(int time, char *message, int id)
// {
	
// }

int	check_fork_and_eat(pthread_mutex_t	*fork)
{
	if (fork)
	{
		pthread_mutex_lock(fork);
		return (1);
	}
	return (0);
}
void eat(t_philo *philo) {
    size_t time = get_current_time() - philo->time;

    pthread_mutex_lock(&philo->left_fork);
    printf("%zu %d %s\n", time, philo->current_philo, "has taken a fork");

    pthread_mutex_lock(&philo->right_fork);
    printf("%zu %d %s\n", time, philo->current_philo, "has taken a fork");

    printf("%zu %d %s\n", time, philo->current_philo, "is eating");
    ft_sleep(philo->time_to_eat);

    pthread_mutex_unlock(&philo->left_fork);
    pthread_mutex_unlock(&philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// printf("%lu %d %s\n", get_current_time() - philo->time,
	// 	philo->current_philo, "is eating");
	eat(philo);
	ft_sleep(philo->time_to_eat);
	printf("%lu %d %s\n", get_current_time() - philo->time,
		philo->current_philo, "is sleeping");
	ft_sleep(philo->time_to_sleep);
	return (NULL);
}

// void	check_simulation(t_data	*data)
// {
// 	if (data->total_philo % 2)
// 		// even number
// 	else
// 		//odd number
// 	// i have to keep going in loop until someone dies so once the philo reaches the end then we need to start from the beginning
// 	// so circular linkned list?? so now we need to change the head, reset the head?
	
// }

void	simulation(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = data->number_of_philo;
	data->dead_flag = 0;
	if (data->total_philo == 1)
	{
		printf("%zu %d %s\n", (get_current_time() + 1 - data->time),
			1, "has taken a fork");
		printf("%zu %d %s\n", (get_current_time() + 1 - data->time), 1, "died");
		data->dead_flag = 1;
		return ;
	}
	while (i < data->total_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			(perror("pthread_create() error"), exit(EXIT_FAILURE));
		if (pthread_join(philo[i].thread, NULL) != 0)
			(perror("pthread_join() error"), exit(EXIT_FAILURE));
		i++;
	}
	// printf("All philosophers have finished their meals.\n");
}
