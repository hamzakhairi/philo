/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:23:33 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/05 10:15:29 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	cheacker_each_philo(t_data *data, int *full)
{
	int		i;
	long	time_since_meal;
	int		count;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		time_since_meal = get_time() - data->philos[i].last_meal;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (time_since_meal >= data->time_to_die)
		{
			print_died_philo(data, data->philos[i].id);
			set_dead(data, 1);
			return (0);
		}
		pthread_mutex_lock(&data->philos[i].eat_count_mutex);
		count = data->philos[i].eat_count;
		if (data->must_eat != -1 && count == data->must_eat)
			(*full)++;
		pthread_mutex_unlock(&data->philos[i].eat_count_mutex);
		i++;
	}
	return (1);
}

void	checker_philo(t_data *data)
{
	int	full;

	while (1)
	{
		if (get_dead(data))
			break ;
		full = 0;
		if (!cheacker_each_philo(data, &full))
			break ;
		if (data->must_eat != -1 && full == data->num_philos)
		{
			data->is_full = 1;
			break ;
		}
	}
}

int	init_join_thread(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->num_philos)
	{
		pthread_join(data->philos[j].thread, NULL);
		j++;
	}
	return (0);
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].fork);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		pthread_mutex_destroy(&data->philos[i].eat_count_mutex);
		i++;
	}
	free(data->philos);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!main_validation(argc, argv))
		return (0);
	if (!init_data(&data, argc, argv))
		return (0);
	if (!validation_number(&data))
		return (0);
	if (!init_pthread_data(&data))
		return (0);
	if (!init_philo(&data))
		return (0);
	if (data.num_philos != 1)
		checker_philo(&data);
	init_join_thread(&data);
	destroy(&data);
	return (0);
}
