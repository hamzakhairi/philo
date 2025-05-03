/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:58:22 by hkhairi           #+#    #+#             */
/*   Updated: 2025/05/01 20:37:11 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int init_pthread_data(t_data *data)
{
    int i;
    int state;

    state = 1;
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
        printf("Failed init pthread data !\n");
        return 0;
    }
    return 1;
}

int init_data(t_data *data, int argc, char *argv[])
{
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 5)
        data->must_eat = 0;
    else
        data->must_eat = ft_atoi(argv[5]);
    data->dead = 0;
    data->start_time = get_time();
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->forks || !data->philos)
    {
        printf("Failed malloc !\n");
        return (0);
    }
    return 1;
}

