/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:06:59 by hkhairi           #+#    #+#             */
/*   Updated: 2025/05/02 16:41:24 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_philo(t_data *data)
{
    int i = 0;

    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].state = 0;
        data->philos[i].eat_count = 0;
        data->philos[i].last_meal = data->start_time;
        data->philos[i].data = data;

        if (pthread_mutex_init(&data->philos[i].eat_count_mutex, NULL) != 0 ||
            pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
        {
            printf("Failed pthread_mutex_init in init philo!\n");
            return 0;
        }

        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        i++;
    }

    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, philo_life, &data->philos[i]) != 0)
        {
            printf("Failed to create pthread for philosopher %d!\n", i + 1);
            return 0;
        }
        i++;
    }

    return 1;
}


