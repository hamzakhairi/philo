/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:19:54 by hkhairi           #+#    #+#             */
/*   Updated: 2025/05/01 10:59:31 by hkhairi          ###   ########.fr       */
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

