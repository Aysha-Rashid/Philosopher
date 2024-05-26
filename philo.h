#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

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
	t_philo	*number_of_philo;
}			t_data;

int		parsing_arg(char **argv);
void	init_philo(char **argv, t_data *data);
void	free_philos(t_data *data);
void	error(char *message);
int		ft_strcmp(char	*str1, char	*str2);
void	simulation(char	**argv, t_data	*data);