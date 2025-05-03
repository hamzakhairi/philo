/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:18:00 by hkhairi           #+#    #+#             */
/*   Updated: 2025/05/01 11:00:48 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int get_dead(t_data *data)
{
    int value;
    pthread_mutex_lock(&data->death);
    value = data->dead;
    pthread_mutex_unlock(&data->death);
    return value;
}

void smart_sleep(int duration, t_data *data)
{
    long start = get_time();
    // while (!data->dead && (get_time() - start < duration))
    while (!get_dead(data) && (get_time() - start < duration))
        usleep(100);
}

void print_status(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->data->print);
    // if (!philo->data->dead)
    if (!get_dead(philo->data))
        printf("%ld\t%d\t%s\n", get_time() - philo->data->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print);
}

void *philo_life(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    //  Delay for even philosophers to prevent contention
    if (philo->data->num_philos == 1)
    {
        print_status(philo, "has taken right fork");
        smart_sleep(philo->data->time_to_die, philo->data);
        print_died_philo(philo->data, philo->id);
        return NULL;
    }

    if (philo->id % 2 == 0)
        usleep(1000);

    // while (!philo->data->dead)
    while (!get_dead(philo->data))
    {
        

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


        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_meal = get_time();
        pthread_mutex_unlock(&philo->meal_mutex);
        
        print_status(philo, "is eating");

        smart_sleep(philo->data->time_to_eat, philo->data);
        
        pthread_mutex_lock(&philo->eat_count_mutex);
        philo->eat_count++;
        pthread_mutex_unlock(&philo->eat_count_mutex);


        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        print_status(philo, "is sleeping");
        smart_sleep(philo->data->time_to_sleep, philo->data);
        print_status(philo, "is thinking");
    }

    return NULL;
}


