/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:04:00 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/05/26 22:04:00 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	philo[200];

	if (argc < 5)
		return (error("less then 5 arg"), 0);
	if (argc > 6)
		return (error("more than 6 arg"), 0);
	if (parsing_arg(argv))
		return (0);
	if (ft_atoi(argv[1]) > 200)
		return (error("Philo is 200"), 0);
	init(argv, &data, philo);
	simulation(&data);
	destory_thread(philo);
	return (0);
}

void	destory_thread(t_philo	*philo)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&philo->data->write);
	pthread_mutex_destroy(&philo->data->death_check);
	pthread_mutex_destroy(&philo->philo_dead);
	pthread_mutex_destroy(&philo->left_fork);
	while (++i < philo->data->total_philo)
	{
		if (philo[i].right_fork != &philo[(i + 1)
				% philo->data->total_philo].left_fork)
			pthread_mutex_destroy(philo[i].right_fork);
	}
}
