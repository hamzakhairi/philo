/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:23:33 by hkhairi           #+#    #+#             */
/*   Updated: 2025/05/02 16:34:34 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



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
            pthread_mutex_lock(&data->philos[i].meal_mutex);
            long time_since_meal = get_time() - data->philos[i].last_meal;
            pthread_mutex_unlock(&data->philos[i].meal_mutex);
            
            if (time_since_meal >= data->time_to_die)
            {
                print_died_philo(data, data->philos[i].id);
                return ;
            }
            pthread_mutex_lock(&data->philos[i].eat_count_mutex);
            int count = data->philos[i].eat_count;
            pthread_mutex_unlock(&data->philos[i].eat_count_mutex);
            
            if (data->must_eat != -1 && count >= data->must_eat)
                full++;
            i++;
        }
        if (data->must_eat != -1 && full == data->num_philos)
        {
            pthread_mutex_lock(&data->print);
            data->dead = 1;
            pthread_mutex_unlock(&data->print);
        }
        usleep(1000);
    }
}

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

int main(int argc , char *argv[])
{
    t_data data;
    if (!main_validation(argc, argv))
        return 0;
    if (!init_data(&data, argc, argv))
        return 0;
    if (!validation_number(&data))
        return 0;
    if (!init_pthread_data(&data))
        return 0;
    if (!init_philo(&data))
        return 0;
    checker_philo(&data);
    init_join_thread(&data);
    destroy(&data);
    return (0);
}

