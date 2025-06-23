/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:33:09 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/05 10:16:13 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	acquire_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->next->fork);
	print_status(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

int	philo_eat(t_philo *philo)
{
	t_data	*data;
	int		count;

	data = philo->data;
	acquire_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	count = philo->eat_count;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	update_last_meal(philo);
	ft_usleep(philo, data->time_to_eat);
	release_forks(philo);
	if (philo->data->must_eat != -1 && count >= philo->data->must_eat)
		return (0);
	return (1);
}

char	*sumilation_one_tread(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_status(philo, "has taken a fork");
	ft_usleep(philo, philo->data->time_to_die);
	print_died_philo(philo->data, philo->id);
	return (NULL);
}

void	*philo_life(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->must_eat == 0)
		return (NULL);
	if (philo->data->time_to_die == 0)
		return (NULL);
	if (philo->data->num_philos == 1)
		return (sumilation_one_tread(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_death(philo) && !philo->data->is_full)
	{
		if (!philo_eat(philo))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo, philo->data->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
