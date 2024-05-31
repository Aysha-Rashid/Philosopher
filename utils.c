/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:35:45 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/05/27 21:35:45 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *message)
{
	if (ft_strcmp(message, "philo_is_zero") == 0)
		printf("Philo cannot be zero\n");
	else if (ft_strcmp(message, "arguments is negative") == 0)
		printf("arguments should be positive integer\n");
	else if (ft_strcmp(message, "Philo is 200") == 0)
		printf("Philo should not be more than 200\n");
	else if (ft_strcmp(message, "more than 6 arg") == 0)
		printf("Too much arguments\n");
	else if (ft_strcmp(message, "less then 5 arg") == 0)
		printf("Too less arguments\n");
}

int	parsing_arg(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (argv[1][0] == '0')
		return (error("philo_is_zero"), 1);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!isdigit(argv[i][j]))
				return (error("arguments is negative"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

void	init_philo(t_data *data, char **argv)
{
	int		i;

	i = 0;
	while (i < data->total_philo)
	{

		data->number_of_philo[i].current_philo = i + 1;
		data->number_of_philo[i].time = get_current_time();
		if (argv[5])
			data->number_of_philo[i].no_of_meal = ft_atoi(argv[5]);
		else
			data->number_of_philo[i].no_of_meal = -1;
		data->number_of_philo[i].time_to_eat = ft_atoi(argv[2]);
		data->number_of_philo[i].time_to_sleep = ft_atoi(argv[4]);
		pthread_mutex_init(&data->number_of_philo[i].left_fork, NULL);
		pthread_mutex_init(&data->number_of_philo[i + 1].right_fork, NULL);
		i++;
	}
}

void	init(char **argv, t_data *data)
{
	int		no_of_philo;

	no_of_philo = ft_atoi(argv[1]);
	data->total_philo = no_of_philo;
	data->number_of_philo = malloc(data->total_philo * sizeof(t_philo));
	if (data->number_of_philo == NULL)
	{
		perror("malloc() error");
		return ;
	}
	init_philo(data, argv);
}

// void	free_philos(t_data *data)
// {
// 	// t_philo	*current;
// 	// t_philo	*temp;
// 	int		i;

// 	// current = data->number_of_philo;
// 	while (i < data->total_philo)
// 	{
// 		free(data->number_of_philo);
// 		i++;
// 	}
// 	data->number_of_philo = NULL;
// }
