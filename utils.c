
#include "philo.h"

void	error(char *message)
{
	if (ft_strcmp(message, "philo_is_zero")== 0)
		printf("Philo cannot be zero\n");
	else if (ft_strcmp(message, "arguments is negative") == 0)
		printf("arguments should be positive\n");
	else if (ft_strcmp(message, "Philo is 200") == 0)
		printf("Philo should not be more than 200\n");
	else if (ft_strcmp(message, "more than 6 arg")== 0)
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

void	init_philo(char **argv, t_data *data)
{
	t_philo	*philo;
	t_philo	*last;
	int		no_of_philo;
	int		i;

	i = 0;
	philo = NULL;
	last = NULL;
	no_of_philo = atoi(argv[1]);
	if (no_of_philo > 200)
	{
		error("Philo is 200");
		return ;
	}
	while (i < no_of_philo)
	{
		philo = malloc(sizeof(t_philo));
		if (philo == NULL)
			exit(EXIT_FAILURE);
		philo->total_philo = no_of_philo;
		philo->time_to_die = atoi(argv[2]);
		philo->time_to_eat = atoi(argv[3]);
		philo->time_to_sleep = atoi(argv[4]);
		if (argv[5])
			philo->no_of_meal = atoi(argv[5]);
		philo->next = NULL;
		if (data->number_of_philo == NULL)
			data->number_of_philo = philo;// only comes here once so they save the value once and i dont have to allocate memory for it
		else
			last->next = philo;
		last = philo;
		i++;
	}
}

void	free_philos(t_data *data)
{
	t_philo	*current;
	t_philo	*temp;

	current = data->number_of_philo;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	data->number_of_philo = NULL;
}
