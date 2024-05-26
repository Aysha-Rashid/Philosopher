
#include "philo.h"

int	parsing_arg(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (argv[1][0] == '0')
		return (printf("%s\n", "cannot be zero"), 1);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!isdigit(argv[i][j]))
				return (printf("%s\n", "arguments should be popsitive numbers"), 1);
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
	while (i < no_of_philo)
	{
		philo = malloc(sizeof(t_philo));
		if (philo == NULL)
			exit(EXIT_FAILURE);
		philo->total_philo = no_of_philo;
		philo->time_to_die = atoi(argv[2]);
		philo->time_to_eat = atoi(argv[3]);
		philo->time_to_sleep = atoi(argv[4]);
		philo->next = NULL;
		if (data->number_of_philo == NULL)
			data->number_of_philo = philo;
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
