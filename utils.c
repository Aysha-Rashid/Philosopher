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

void	init_philo(t_data	*data, char	**argv)
{
	int	i;
	int	no_of_philo;

	i = 0;
	no_of_philo = ft_atoi(argv[1]);
	data->total_philo = no_of_philo;
	while (i < data->total_philo)
	{
		data->resources[i].meal_finish = 0;
		data->resources[i].current_philo = i + 1;
		data->resources[i].time_to_die = ft_atoi(argv[2]);
		data->resources[i].time_to_eat = ft_atoi(argv[3]);
		data->resources[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			data->resources[i].no_of_meal = ft_atoi(argv[5]);
		else
			data->resources[i].no_of_meal =	-1;
		data->resources[i].last_meal_time = get_current_time();
		data->resources[i].data = data;
		pthread_mutex_init(&data->resources[i].left_fork, NULL);
		pthread_mutex_init(&data->resources[i].write, NULL);
		pthread_mutex_init(&data->resources[i].philo_dead, NULL);
		if (i == data->total_philo - 1)
			data->resources[i].right_fork = &data->resources[0].left_fork;
		else
			data->resources[i].right_fork = &data->resources[i + 1].left_fork;
		// pthread_mutex_init(&data->resources[(i + 1) % no_of_philo].right_fork,
		// 	NULL);
		i++;
	}
}

// void	init(char **argv, t_data *data)
// {
// 	int	no_of_philo;

// 	no_of_philo = ft_atoi(argv[1]);
// 	data->total_philo = no_of_philo;
// 	data->resources = malloc(sizeof(t_philo) * data->total_philo );
// 	if (data->resources == NULL)
// 	{
// 		perror("malloc() error");
// 		exit(EXIT_FAILURE);
// 	}
// 	data->dead_flag = 0;
// 	init_philo(data, argv);
// 	pthread_mutex_init(&data->death_check, NULL);
// }

void init(char **argv, t_data *data)
{
    int no_of_philo;

    no_of_philo = ft_atoi(argv[1]);
    data->total_philo = no_of_philo;
    data->resources = malloc(sizeof(t_philo) * data->total_philo);
    if (data->resources == NULL)
    {
        perror("malloc() error");
        exit(EXIT_FAILURE);
    }
    data->dead_flag = 0;
    init_philo(data, argv);
    pthread_mutex_init(&data->death_check, NULL);
}


// void	free_philos(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->total_philo > i)
// 	{
// 		pthread_mutex_destroy(data->resources[i].thread);
// 		i++;
// 	}
// 	free(data->resources);
// 	data->resources = NULL;
// }
