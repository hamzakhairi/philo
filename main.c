#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct s_data t_data;

typedef struct s_philo {
    int id;
    int state;
    int eat_count;
    long last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    t_data *data;
} t_philo;

struct s_data {
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int dead;
    long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t death;
    t_philo *philos;
};

long get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void smart_sleep(int duration, t_data *data)
{
    long start = get_time();
    while (!data->dead && (get_time() - start < duration))
        usleep(100);
}

void print_died_philo(t_data *data, int id)
{
    pthread_mutex_lock(&data->print);
    data->dead = 1;
    printf("%ld\t%d\tdied\n", get_time() - data->start_time, id);
    pthread_mutex_unlock(&data->print);
}

void print_status(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->data->print);
    if (!philo->data->dead)
        printf("%ld\t%d\t%s\n", get_time() - philo->data->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print);
}

int check_number(t_data *data)
{
    if (data->num_philos < 1 || data->time_to_die < 60 || data->time_to_eat < 60
        || data->time_to_sleep < 60)
        return 0;
    return 1;
}

int init_data(t_data *data, int argc, char *argv[])
{
    data->num_philos = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    if (argc == 6)
        data->must_eat = atoi(argv[5]);
    else
        data->must_eat = -1;
    data->start_time = get_time();
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    data->dead = 0;
    if (!check_number(data))
        return 0;
    return 1;
}

int init_pthread_mutex(t_data *data)
{
    int i;
    int state = 1;

    if (0 != pthread_mutex_init(&data->print, NULL))
        state = 0;
    if (0 != pthread_mutex_init(&data->death, NULL))
        state = 0;
    i = 0;
    while (i < data->num_philos)
    {
        if (0 != pthread_mutex_init(&data->forks[i], NULL))
            state = 0;
        i++;
    }
    if (!state)
    {
        printf("Failed init pthread mutex!\n");
        return 0;
    }
    return 1;
}

void *philo_life(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // ✅ Delay for even philosophers to prevent contention
    if (philo->data->num_philos == 1)
    {
        print_status(philo, "has taken right fork");
        smart_sleep(philo->data->time_to_die, philo->data);
        print_died_philo(philo->data, philo->id);
        return NULL;
    }

    if (philo->id % 2 == 0)
        usleep(1000);

    while (!philo->data->dead)
    {
        print_status(philo, "is thinking");

        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken left fork");
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken right fork");
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken right fork");
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken left fork");
        }

        // ✅ Update last_meal BEFORE eating
        philo->last_meal = get_time();
        print_status(philo, "is eating");

        smart_sleep(philo->data->time_to_eat, philo->data); // ✅ Better sleep
        philo->eat_count++;

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        print_status(philo, "is sleeping");
        smart_sleep(philo->data->time_to_sleep, philo->data); // ✅ Better sleep
    }

    return NULL;
}


int init_philo(t_data *data)
{
    int i = 0;

    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].state = THINKING;
        data->philos[i].eat_count = 0;
        data->philos[i].last_meal = data->start_time;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].data = data;

        if (pthread_create(&data->philos[i].thread, NULL, philo_life, &data->philos[i]) != 0)
        {
            printf("Failed to create pthread for philosopher!\n");
            return 0;
        }
        i++;
    }
    return 1;
}



void checker_philo(t_data *data)
{
    int i;
    int full;

    while (1)
    {
        if (data->dead)
            break;

        i = 0;
        full = 0;

        while (i < data->num_philos)
        {
            if ((get_time() - data->philos[i].last_meal) > data->time_to_die)
            {
                print_died_philo(data, data->philos[i].id);
                return;
            }

            // check if must_eat is reached
            if (data->must_eat != -1 && data->philos[i].eat_count >= data->must_eat)
                full++;

            i++;
        }

        if (data->must_eat != -1 && full == data->num_philos)
        {
            pthread_mutex_lock(&data->print);
            data->dead = 1;
            pthread_mutex_unlock(&data->print);
            return;
        }

        usleep(1000);
    }
}


void init_join_thread(t_data *data)
{
    int i = 0;
    while (i < data->num_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
}

void destroy(t_data *data)
{
    int i = 0;
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->death);
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    free(data->forks);
    free(data->philos);
}

int main(int argc, char *argv[])
{
    t_data data;
    memset(&data, 0, sizeof(t_data));

    if (argc != 5 && argc != 6)
    {
        printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep [must_eat]\n", argv[0]);
        return 1;
    }

    if (!init_data(&data, argc, argv))
        return 1;
    if (!init_pthread_mutex(&data))
        return 1;
    if (!init_philo(&data))
        return 1;

    checker_philo(&data);
    init_join_thread(&data);
    destroy(&data);

    return 0;
}
