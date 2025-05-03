/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:15:07 by hkhairi           #+#    #+#             */
/*   Updated: 2025/05/01 10:59:52 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//? i do state 0 becouse 0 is thinking 
int init_join_thread(t_data *data)
{
    int j = 0;

    while (j < data->num_philos)
    {
        pthread_join(data->philos[j].thread, NULL);
        j++;
    }
    return 0;
}

int init_philosopher(t_data *data)
{
    int i = 0;

    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].state =  0;
        data->philos[i].eat_count = data->must_eat;
        data->philos[i].last_meal = data->start_time;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].data = data;
        // data->philos[i].meal_mutex = malloc(sizeof(pthread_mutex_t));
        // data->philos[i].eat_count_mutex = malloc(sizeof(pthread_mutex_t));
        // if (!data->philos[i].meal_mutex || !data->philos[i].eat_count_mutex)
        //     return 0;
        if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
            return 0;
        if (pthread_mutex_init(&data->philos[i].eat_count_mutex, NULL) != 0)
            return 0;
        if (pthread_create(&data->philos[i].thread, NULL, philo_life, &data->philos[i]) != 0)
        {
            free(data->forks);
            free(data->philos);
            return 0;               
        }
        i++;
    }
    return 1;
}

int init_pthread_mutex(t_data *data)
{
    int i = 0;
    int state = 1;
    
    if (0 != pthread_mutex_init(&data->death, NULL))
        state = 0;
    if (0 != pthread_mutex_init(&data->print, NULL))
        state = 0;
    while (i < data->num_philos)
    {
        if (0 != pthread_mutex_init(&data->forks[i], NULL))
            state = 0;
        i++;
    }
    if (!state)
        return (print("Failde pthread mutex !\n"), 1);
    return (0);
}

int check_number(t_data *data)
{
    if (data->num_philos < 1 || data->time_to_die < 60 || data->time_to_eat < 60
        || data->time_to_sleep < 60)
        return 0;
    return 1;
}

int init_philo(t_data *data, int argc , char *argv[])
{
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->must_eat = ft_atoi(argv[5]);
    else 
        data->must_eat = -1;    
    data->dead = 0;
    data->start_time = get_time();
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return 0;
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->philos)
    {
        free(data->forks);
        return 0;
    }
    if (!check_number(data))
        return 0;
    return 1;
}



