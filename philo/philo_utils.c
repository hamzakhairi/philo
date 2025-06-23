/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:29:37 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/03 20:55:28 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	set_dead(t_data *data, int value)
{
	pthread_mutex_lock(&data->death);
	data->dead = value;
	pthread_mutex_unlock(&data->death);
}

int	get_dead(t_data	*data)
{
	int	value;

	pthread_mutex_lock(&data->death);
	value = data->dead;
	pthread_mutex_unlock(&data->death);
	return (value);
}

int	check_death(t_philo *philo)
{
	int	value;

	value = 0;
	pthread_mutex_lock(&philo->data->death);
	value = philo->data->dead;
	pthread_mutex_unlock(&philo->data->death);
	return (value);
}
