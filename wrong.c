void	print_action(t_data	*data, int id, char *message)
{
	pthread_mutex_lock(&data->write);
	if (!data->dead_flag)
		printf("%zu %d %s\n", get_current_time()
			- data->time, id, message);
	pthread_mutex_unlock(&data->write);
}

void	eat(t_philo *philo, t_data *data)
{
	if (data->dead_flag || data->resources->meal_finish)
		return ;
	if (philo->current_philo % 2 == 0)
		usleep(1000);
	if (data->dead_flag || data->resources->meal_finish)
		return ;
	pthread_mutex_lock(philo->right_fork);
	print_action(data, philo->current_philo, "has taken a fork");
	if (data->dead_flag)
		return ;
	pthread_mutex_lock(&philo->left_fork);
	print_action(data, philo->current_philo, "has taken a fork");
	if (data->dead_flag)
		return ;
	pthread_mutex_lock(&data->death_check);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&data->death_check);
	if (!data->dead_flag)
	{
		print_action(data, philo->current_philo, "is eating");
		ft_sleep(philo->time_to_eat);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!philo->data->dead_flag && !philo->meal_finish)
	{
		if (philo->data->dead_flag)
			return (NULL);
		eat(philo, philo->data);
		if (philo->data->dead_flag)
			return (NULL);
		if (philo->no_of_meal > 0)
			philo->no_of_meal--;
		if (philo->data->dead_flag)
			return (NULL);
		print_action(philo->data, philo->current_philo, "is sleeping");
		if (philo->data->dead_flag)
			return (NULL);
		ft_sleep(philo->time_to_sleep);
		if (philo->data->dead_flag)
			return (NULL);
		print_action(philo->data, philo->current_philo, "is thinking");
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (!data->dead_flag || !data->resources->meal_finish)
	{
		while (i++ < data->total_philo)
		{
			pthread_mutex_lock(&data->resources[i].philo_dead);
			if ((get_current_time() - data->resources[i].last_meal_time)
				>= data->resources[i].time_to_die)
			{
				print_action(data, data->resources[i].current_philo, "died");
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->resources[i].philo_dead);
				return (NULL);
			}
			pthread_mutex_unlock(&data->resources[i].philo_dead);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*simulation(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = -1;
	data->time = get_current_time();
	if (data->total_philo == 1)
	{
		pthread_mutex_lock(&data->resources->left_fork);
		print_action(data, 1, "has taken a fork");
		pthread_mutex_unlock(&data->resources->left_fork);
	}
	while (++i < data->total_philo && data->total_philo != 1)
	{
		if (pthread_create(&data->resources[i].thread, NULL,
				routine, &data->resources[i]) != 0)
			return (perror("pthread_create() error"), NULL);
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
		return (perror("pthread_create() error"), NULL);
	i = -1;
	while (++i < data->total_philo && data->total_philo != 1)
	{
		if (pthread_join(data->resources[i].thread, NULL) != 0)
			return (perror("pthread_join() error"), NULL);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (perror("pthread_join() error"), NULL);
	return (NULL);
}
