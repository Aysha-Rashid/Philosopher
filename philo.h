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
	int				current_philo;
	int				meal_finish;
	int				every_die;
	int				no_of_meal;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	size_t			last_meal_time;
	pthread_mutex_t	philo_dead;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				total_philo;
	int				dead_flag;
	size_t			time;
	t_philo			*resources;
	pthread_mutex_t	write;
	pthread_mutex_t	death_check;
}				t_data;

int		parsing_arg(char **argv);
void	init(char **argv, t_data *data, t_philo	*philo);
void	error(char *message);
int		ft_strcmp(char	*str1, char	*str2);
void	*simulation(t_data	*data);
size_t	get_current_time(void);
void	ft_sleep(size_t	milliseconds);
int		overflow(long max, long r, int sign);
int		ft_atoi(const char	*str);
int		ft_isdigit(int c);
void	handle_one(t_data	*data);
void	destory_thread(t_philo	*philo);
void	print_action(t_data *data, int id, char *message);
void	every_die(t_data *data);