/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utiles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:13:12 by hkhairi           #+#    #+#             */
/*   Updated: 2025/04/29 15:33:09 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



long get_time()
{ 
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void set_dead(t_data *data, int value)
{
    pthread_mutex_lock(&data->death);
    data->dead = value;
    pthread_mutex_unlock(&data->death);
}

void print_died_philo(t_data *data , int id)
{
    pthread_mutex_lock(&data->print);
    set_dead(data, 1);
    // print("");
    printf("%ld\t%d\tdied\n", get_time() - data->start_time, id);
    pthread_mutex_unlock(&data->print);
}

