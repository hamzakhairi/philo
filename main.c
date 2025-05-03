/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:32:57 by hkhairi           #+#    #+#             */
/*   Updated: 2025/05/01 11:00:06 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void destroy(t_data *data)
{
    int i = 0;
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->death);
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i].meal_mutex);
        pthread_mutex_destroy(&data->philos[i].eat_count_mutex);
        // free(data->philos[i].meal_mutex);
        // free(data->philos[i].eat_count_mutex);
        i++;
    }
    free(data->forks);
    free(data->philos);
}

int main(int argc, char **argv)
{
    t_data data;

    memset(&data, 0, sizeof(t_data));
    if (!main_validation(argc, argv))
        return (1);
    if (!init_philo(&data, argc, argv))
    {
        print("Failed init Philosophers\n");
        return (1);
    }
    init_philosopher(&data);
    init_pthread_mutex(&data);
    checker_philo(&data);
    init_join_thread(&data);
    destroy(&data);
    return (0);
}



