/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_tow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:15:10 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/03 23:32:02 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_died_philo(t_data *data, int id)
{
	pthread_mutex_lock(&data->print);
	printf("%ld\t%d\tdied\n", get_time() - data->start_time, id);
	pthread_mutex_unlock(&data->print);
}

void	print_status(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->start_time;
	if (!get_dead(philo->data))
		printf("%ld\t%d\t%s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	ft_usleep(t_philo *philo, long duration)
{
	long	start;

	start = get_time();
	while (!check_death(philo))
	{
		if (get_time() - start >= duration)
			break ;
		usleep(100);
	}
}
