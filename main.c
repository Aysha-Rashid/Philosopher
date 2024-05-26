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

// number_of_philosophers;
// time_to_die;
// time_to_eat;
// time_to_sleep;
// number_of_times_each_philosopher_must_eat;

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.number_of_philo = 0;
	if (argc < 5)
		return (error("less then 5 arg"), 0);
	if (argc > 6)
		return (error("more than 6 arg"), 0);
	if (parsing_arg(argv))
		return (0);
	init_philo(argv, &data);
	simulation(argv, &data);
		// create thread
		// simulation
	free_philos(&data);
	return (0);
}

//keep checking how many fork they have by their side
//how many times they are eating
// give priority to the one who ate less