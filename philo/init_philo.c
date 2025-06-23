/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:06:59 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 14:17:16 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_data(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->print);
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].fork);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		pthread_mutex_destroy(&data->philos[i].eat_count_mutex);
		i++;
	}
	free(data->philos);
}

int	creat_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_life, &data->philos[i]) != 0)
		{
			destroy_data(data);
			return (printf("Failed to create pthread !\n"), 0);
		}
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

void	check_pthread_fail(t_data *data, int i, int yes)
{
	if (yes)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		pthread_mutex_destroy(&data->philos[i].fork);
	}
	while (--i >= 0)
	{
		pthread_mutex_destroy(&data->philos[i].fork);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		pthread_mutex_destroy(&data->philos[i].eat_count_mutex);
	}
	destroy_data(data);
	printf("Failed pthread_mutex_init in init philo!\n");
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
		data->philos[i].last_meal = 0;
		if (pthread_mutex_init(&data->philos[i].eat_count_mutex, NULL) != 0)
			return (check_pthread_fail(data, i, 0), 0);
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (check_pthread_fail(data, i, 1), 0);
		if (pthread_mutex_init(&data->philos[i].fork, NULL) != 0)
			return (check_pthread_fail(data, i, 1), 0);
		if (i + 1 == data->num_philos)
			data->philos[i].next = &data->philos[0];
		else
			data->philos[i].next = &data->philos[i + 1];
		i++;
	}
	if (!creat_thread(data))
		return (0);
	return (1);
}
