/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:36:38 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/04 22:16:18 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

void	print_status(t_philo *philo, char *status, int keep_lock)
{
	sem_wait(philo->data->protect_data);
	if (philo->data->is_died)
	{
		sem_post(philo->data->protect_data);
		return ;
	}
	sem_post(philo->data->protect_data);
	sem_wait(philo->data->print_status);
	printf("%ld\t%d\t%s\n", get_time() - philo->data->time_start,
		philo->id, status);
	if (!keep_lock)
		sem_post(philo->data->print_status);
}

int	check_death(t_philo *philo)
{
	sem_wait(philo->data->protect_data);
	if (philo->data->is_died)
	{
		sem_post(philo->data->protect_data);
		return (1);
	}
	sem_post(philo->data->protect_data);
	return (0);
}

int	check_last_meal(t_philo *philo)
{
	sem_wait(philo->protect_philo);
	sem_wait(philo->data->protect_data);
	if ((get_time() - philo->last_meal) > philo->data->time_died_ph)
	{
		sem_post(philo->data->protect_data);
		sem_post(philo->protect_philo);
		return (1);
	}
	sem_post(philo->data->protect_data);
	sem_post(philo->protect_philo);
	return (0);
}

void	set_died(t_philo *philo)
{
	sem_wait(philo->data->protect_data);
	philo->data->is_died = 1;
	sem_post(philo->data->protect_data);
}
