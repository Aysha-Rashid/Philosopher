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

	data.number_of_philo = 0;
	if (argc < 5)
		return (error("less then 5 arg"), 0);
	if (argc > 6)
		return (error("more than 6 arg"), 0);
	if (parsing_arg(argv))
		return (0);
	if (ft_atoi(argv[1]) > 200)
	{
		error("Philo is 200");
		return (0);
	}
	init_philo(argv, &data);
	simulation(argv, &data);
		// create thread
		// simulation
	free_philos(&data);
	return (0);
}

// int i = 0;
// void *count_to_100(void *arg)
// {
//  (void)arg;
// // 
// //  for(int i = 0; i < 10000000; i++)
// //  {
// //  	printf("i = %d, The count has finished\n", i);
// //  }
// 	while (i < 1000000000)
// 		i++;
//  return (NULL);
// }

// void *print_hello(void *arg)
// {
//  (void)arg;
// 	while (i < 1000000000)
// 		i++;
//  return (NULL);
// }

// int main()
// {
//  pthread_t thread_1;
//  pthread_t thread_2;

//  pthread_create(&thread_1, NULL, count_to_100, NULL);
//  pthread_create(&thread_2, NULL, print_hello, NULL);
//   pthread_join(thread_1, NULL);
//  pthread_join(thread_2, NULL);
//  printf("%d\n", i);
// }

//keep checking how many fork they have by their side
//how many times they are eating
//give priority to the one who ate less