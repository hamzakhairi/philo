/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:58:22 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/02 23:49:22 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_pthread_data(t_data *data)
{
	if (0 != pthread_mutex_init(&data->print, NULL))
		return (free(data->philos),
			printf("Failed : init mutex: print\n"), 0);
	if (0 != pthread_mutex_init(&data->death, NULL))
		return (free(data->philos),
			printf("Failed : init mutex: print\n"), 0);
	return (1);
}

int	init_data(t_data *data, int argc, char *argv[])
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->must_eat = -1;
	else
		data->must_eat = ft_atoi(argv[5]);
	data->dead = 0;
	data->is_full = 0;
	data->start_time = get_time();
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		printf("Failed malloc !\n");
		return (0);
	}
	return (1);
}
