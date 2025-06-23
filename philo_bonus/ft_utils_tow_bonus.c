/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_tow_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:15:35 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 14:51:11 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

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

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

char	*genret_name(char *str, int index)
{
	char	*index_str;
	char	*filename;

	index_str = ft_itoa(index);
	if (!index_str)
	{
		free(index_str);
		return (NULL);
	}
	filename = ft_strjoin(str, index_str);
	if (!filename)
	{
		free(index_str);
		return (NULL);
	}
	free(index_str);
	return (filename);
}

void	check_counter_meals(t_philo *philo)
{
	sem_wait(philo->data->protect_data);
	philo->data->finished_meals++;
	if (philo->data->finished_meals >= philo->data->counter)
	{
		philo->data->is_died = 1;
	}
	sem_post(philo->data->protect_data);
}
