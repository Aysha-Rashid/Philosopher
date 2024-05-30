/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:35:31 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/05/27 21:35:31 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				total_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_of_meal;
	struct s_philo	*next;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t				left_fork;
	pthread_mutex_t				right_fork;
	int							current_philo;
	int							dead_flag;
	size_t						time;
	t_philo						*number_of_philo;
}			t_data;

int		parsing_arg(char **argv);
void	init_philo(char **argv, t_data *data);
void	free_philos(t_data *data);
void	error(char *message);
int		ft_strcmp(char	*str1, char	*str2);
void	simulation(char	**argv, t_data	*data);
size_t	get_current_time(void);
size_t	ft_sleep(size_t	milliseconds);