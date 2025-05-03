/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:04:06 by hkhairi           #+#    #+#             */
/*   Updated: 2025/05/01 20:38:40 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int validation_number(t_data *data)
{
    if (data->num_philos < 1 || data->time_to_die < 60 || data->time_to_eat < 60 
        || data->time_to_sleep < 60)
    {
        free(data->forks);
        free(data->philos);
        printf("Failed argument !\n");
        return 0;
    }
    return 1;
}

int validation_integer(int argc, char *argv[])
{
    int i;
    int j;

    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
            {
                printf("Error parsing : invalid argument\n");
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int main_validation(int argc, char *argv[])
{
    if (argc > 6 || argc <  5)
    {
        printf("Usage : ./philo  \n --> [number_of_philosophers]\n --> [time_to_die]\n --> [time_to_eat]\n --> [time_to_sleep]\n --> [number_of_times_each_philosopher_must_eat]\n");
        return (0);
    }
    if (!validation_integer(argc, argv))
        return (0);
    
    return 1;
}
