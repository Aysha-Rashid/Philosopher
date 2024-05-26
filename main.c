// number_of_philosophers;
// time_to_die;
// time_to_eat;
// time_to_sleep;
// number_of_times_each_philosopher_must_eat;

#include "philo.h"
int main(int argc, char **argv)
{
	t_data data = {NULL};

	if (argc != 5)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	if (parsing_arg(argv))
		return (1);
	init_philo(argv, &data);
	// create thread
	// simulation
	free_philos(&data);
	return (0);
}