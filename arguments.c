/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:56:20 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/05/30 18:57:50 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

//void  time_to_eat
//void  time_to_sleep
//void  time_to_think

// void	simulation_message(int time, char *message, int id)
// {
	
// }

// void	check_fork_and_eat()
void	eat(t_data	*data, t_philo	*philo)
{
	size_t	time;

	time = get_current_time() + 1 - data->time;
	// pthread_mutex_lock(philo->)
	printf("%zu %d %s\n", time, data->current_philo, "has taken a fork");

}

void	simulation(char	**argv, t_data	*data)
{
	data->dead_flag = 0; // turns one when there is a death or number of meal is done
	if (data->number_of_philo->total_philo == 1)
	{
		// eat(data, data->number_of_philo);
		printf("%zu %d %s\n", (get_current_time() + 1 - data->time), 1, "has taken a fork");
		printf("%zu %d %s\n", (get_current_time() + 1 - data->time), 1, "died");
		data->dead_flag = 1;
		return ;
	}
	t_philo *philo= data->number_of_philo;
	size_t i = 0; // remove it, it was just for testing
	data->current_philo = 0;
	while (!data->dead_flag && philo)
	{
		printf("%zu", (get_current_time() - data->time));
		ft_sleep(1);//doing something
		printf("\nsimulation\n");
		// check for the forks and whether they should eat or not
		// check if they have forks on both side
		// check_fork_and_eat(data->current_philo, data->dead_flag, data->number_of_philo);
		if (data->number_of_philo->no_of_meal)
		{
			// printf("which philo? philo number : %d\n", data->current_philo);
			// printf("number of meals per philo: %d\n", data->number_of_philo->no_of_meal);
			data->number_of_philo->no_of_meal--;
		}
		if (data->number_of_philo->no_of_meal == 0)
		{
			printf("ate all meals\n");
			break ;
		}
		if (i > 5)
		{
			data->dead_flag = 1;
			break ;
		}
		i++;
		philo = philo->next;
		data->current_philo++;
		printf("current->philo %d\n", data->current_philo);
	}
	if (data->dead_flag)
		printf("%zu %d %s\n", (get_current_time() - data->time), data->current_philo, "died");
}
