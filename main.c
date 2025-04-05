#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct s_philo {
    int id;
    int state;
    int eat_count;
    long last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    struct s_data *data;
} t_philo;

typedef struct s_data {
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int dead;
    long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    t_philo *philos;
} t_data;

long get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_status(t_philo *philo, char *status) {
    pthread_mutex_lock(&philo->data->print);
    if (!philo->data->dead) {
        printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, status);
    }
    pthread_mutex_unlock(&philo->data->print);
}

void eat(t_philo *philo) {
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork");
    philo->state = EATING;
    print_status(philo, "is eating");
    philo->last_meal = get_time();
    usleep(philo->data->time_to_eat * 1000);
    philo->eat_count++;
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void *philo_life(void *arg) {
    t_philo *philo = (t_philo *)arg;
    while (!philo->data->dead) {
        eat(philo);
        if (philo->data->must_eat != -1 && philo->eat_count >= philo->data->must_eat) {
            break;
        }
        print_status(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
        print_status(philo, "is thinking");
    }
    return NULL;
}

void monitor(t_data *data) {
    int i;
    while (!data->dead) {
        for (i = 0; i < data->num_philos; i++) {
            if (get_time() - data->philos[i].last_meal > data->time_to_die) {
                pthread_mutex_lock(&data->print);
                data->dead = 1;
                printf("%ld %d died\n", get_time() - data->start_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print);
                return;
            }
        }
        usleep(1000);
    }
}

int main(int argc, char **argv) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    t_data data;
    data.num_philos = atoi(argv[1]);
    data.time_to_die = atoi(argv[2]);
    data.time_to_eat = atoi(argv[3]);
    data.time_to_sleep = atoi(argv[4]);
    data.must_eat = argc == 6 ? atoi(argv[5]) : -1;
    data.dead = 0;
    data.start_time = get_time();

    data.forks = malloc(sizeof(pthread_mutex_t) * data.num_philos);
    data.philos = malloc(sizeof(t_philo) * data.num_philos);

    pthread_mutex_init(&data.print, NULL);
    for (int i = 0; i < data.num_philos; i++) {
        pthread_mutex_init(&data.forks[i], NULL);
    }

    for (int i = 0; i < data.num_philos; i++) {
        data.philos[i].id = i + 1;
        data.philos[i].state = THINKING;
        data.philos[i].eat_count = 0;
        data.philos[i].last_meal = data.start_time;
        data.philos[i].left_fork = &data.forks[i];
        data.philos[i].right_fork = &data.forks[(i + 1) % data.num_philos];
        data.philos[i].data = &data;
        pthread_create(&data.philos[i].thread, NULL, philo_life, &data.philos[i]);
    }

    monitor(&data);

    for (int i = 0; i < data.num_philos; i++) {
        pthread_join(data.philos[i].thread, NULL);
    }

    for (int i = 0; i < data.num_philos; i++) {
        pthread_mutex_destroy(&data.forks[i]);
    }
    pthread_mutex_destroy(&data.print);

    free(data.forks);
    free(data.philos);

    return 0;
}