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

//keep checking how many fork they have by their side
//how many times they are eating
//give priority to the one who ate less