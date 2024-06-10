#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_PHILOSOPHERS 4

typedef struct t_data t_data;

typedef struct {
    int current_philo;
    pthread_mutex_t left_fork;
    pthread_mutex_t *right_fork;
    size_t last_meal_time;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int no_of_meal;
    t_data *data;
    pthread_t thread;
} t_philo;

struct t_data {
    int total_philo;
    int dead_flag;
    size_t time;
    t_philo *resources;
    pthread_mutex_t death_check;
};

size_t get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (size_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_sleep(int milliseconds) {
    usleep(milliseconds * 1000);
}

void *monitor(void *arg) {
    t_data *data = (t_data *)arg;
    while (!data->dead_flag)
    {
        pthread_mutex_lock(&data->death_check);
        for (int i = 0; i < data->total_philo && !data->dead_flag; i++) {
            if ((get_current_time() - data->resources[i].last_meal_time) > data->resources[i].time_to_die) {
                printf("%zu %d %s\n", get_current_time() - data->time, data->resources[i].current_philo, "died");
                data->dead_flag = 1;
                pthread_mutex_unlock(&data->death_check);
                break;
            }
        }
        pthread_mutex_unlock(&data->death_check);
        usleep(1000);
    }
    return NULL;
}

void eat(t_philo *philo, t_data *data) {
    if (!data->dead_flag) {
        if (philo->current_philo % 2 == 0) {
            pthread_mutex_lock(&philo->left_fork);
            printf("%zu %d %s\n", get_current_time() - data->time, philo->current_philo, "has taken a fork");
            pthread_mutex_lock(philo->right_fork);
            printf("%zu %d %s\n", get_current_time() - data->time, philo->current_philo, "has taken a fork");
        } else {
            pthread_mutex_lock(philo->right_fork);
            printf("%zu %d %s\n", get_current_time() - data->time, philo->current_philo, "has taken a fork");
            pthread_mutex_lock(&philo->left_fork);
            printf("%zu %d %s\n", get_current_time() - data->time, philo->current_philo, "has taken a fork");
        }
        pthread_mutex_lock(&data->death_check);
        philo->last_meal_time = get_current_time();
        pthread_mutex_unlock(&data->death_check);

        printf("%zu %d %s\n", get_current_time() - data->time, philo->current_philo, "is eating");
        ft_sleep(philo->time_to_eat);

        pthread_mutex_unlock(&philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
}

void *routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    while (!philo->data->dead_flag && philo->no_of_meal != 0) {
        eat(philo, philo->data);
        if (philo->data->dead_flag) {
            return NULL;
        }
        printf("%zu %d %s\n", get_current_time() - philo->data->time, philo->current_philo, "is sleeping");
        ft_sleep(philo->time_to_sleep);
        printf("%zu %d %s\n", get_current_time() - philo->data->time, philo->current_philo, "is thinking");
        if (philo->no_of_meal > 0) {
            philo->no_of_meal--;
        }
    }
    return NULL;
}

void *simulation(t_data *data) {
    pthread_t monitor_thread;
    int i;

    data->time = get_current_time();
    if (data->total_philo == 1) {
        pthread_mutex_lock(&data->resources->left_fork);
        printf("%zu %d %s\n", get_current_time() - data->time, data->resources->current_philo, "has taken a fork");
    }

    for (i = 0; i < data->total_philo; i++) {
        if (pthread_create(&data->resources[i].thread, NULL, routine, &data->resources[i]) != 0) {
            perror("pthread_create() error");
            return NULL;
        }
    }

    if (pthread_create(&monitor_thread, NULL, monitor, data) != 0) {
        perror("pthread_create() error");
        return NULL;
    }

    for (i = 0; i < data->total_philo; i++) {
        if (pthread_join(data->resources[i].thread, NULL) != 0) {
            perror("pthread_join() error");
            return NULL;
        }
    }

    if (pthread_join(monitor_thread, NULL) != 0) {
        perror("pthread_join() error");
        return NULL;
    }

    return NULL;
}

int main() {
    t_data data;
    t_philo philosophers[NUM_PHILOSOPHERS];
    int i;

    data.total_philo = NUM_PHILOSOPHERS;
    data.dead_flag = 0;
    data.resources = philosophers;
    pthread_mutex_init(&data.death_check, NULL);

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].current_philo = i + 1;
        philosophers[i].last_meal_time = get_current_time();
        philosophers[i].time_to_eat = 200; // 2 seconds
        philosophers[i].time_to_sleep = 200; // 3 seconds
        philosophers[i].time_to_die = 200; // 10 seconds
        philosophers[i].no_of_meal = 7; // Number of meals each philosopher should have
        philosophers[i].data = &data;
        pthread_mutex_init(&philosophers[i].left_fork, NULL);
        if (i == NUM_PHILOSOPHERS - 1) {
            philosophers[i].right_fork = &philosophers[0].left_fork;
        } else {
            philosophers[i].right_fork = &philosophers[i + 1].left_fork;
        }
    }

    simulation(&data);

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&philosophers[i].left_fork);
    }
    pthread_mutex_destroy(&data.death_check);

    return 0;
}
