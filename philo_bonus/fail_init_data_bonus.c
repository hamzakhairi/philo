/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_init_data_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:10:54 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 14:18:35 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

void	cleanup_fork_philo_index(t_data *data, int count)
{
	int	i;

	i = 0;
	if (data->fork_each_ph)
	{
		while (i < count)
		{
			if (data->fork_each_ph[i] != SEM_FAILED)
				sem_close(data->fork_each_ph[i]);
			i++;
		}
		free(data->fork_each_ph);
		data->fork_each_ph = NULL;
	}
}

void	cleanup_name_fork_index(t_data *data, int count)
{
	int	i;

	i = 0;
	if (data->name_forks)
	{
		i = 0;
		while (i < count)
		{
			if (data->name_forks[i])
			{
				sem_unlink(data->name_forks[i]);
				free(data->name_forks[i]);
			}
			i++;
		}
		free(data->name_forks);
		data->name_forks = NULL;
	}
}

void	cleanup_fork_arrays(t_data *data, int count)
{
	cleanup_fork_philo_index(data, count);
	cleanup_name_fork_index(data, count);
}

void	cleanup_semaphores(t_data *data)
{
	if (data->print_status != SEM_FAILED)
	{
		sem_close(data->print_status);
		sem_unlink("/print");
	}
	if (data->protect_data != SEM_FAILED)
	{
		sem_close(data->protect_data);
		sem_unlink("/protect_data");
	}
}

void	handel_faild(t_data *data, int fork_count)
{
	cleanup_fork_arrays(data, fork_count);
	cleanup_semaphores(data);
	printf("Failed : allocation memory !\n");
}
