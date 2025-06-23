/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_init_philo_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:12:45 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 15:10:40 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

void	cleanup_fork_each_philo(t_data *data)
{
	int	i;

	i = 0;
	if (data->fork_each_ph)
	{
		while (i < data->counter)
		{
			if (data->fork_each_ph[i] != SEM_FAILED)
				sem_close(data->fork_each_ph[i]);
			i++;
		}
		free(data->fork_each_ph);
	}
}

void	cleanup_name_fork(t_data *data)
{
	int	i;

	i = 0;
	if (data->name_forks)
	{
		i = 0;
		while (i < data->counter)
		{
			if (data->name_forks[i])
			{
				sem_unlink(data->name_forks[i]);
				free(data->name_forks[i]);
			}
			i++;
		}
		free(data->name_forks);
	}
}

void	cleanup_all_resources(t_data *data)
{
	int	i;

	i = 0;
	cleanup_fork_each_philo(data);
	cleanup_name_fork(data);
	if (data->protect_data != SEM_FAILED)
	{
		sem_close(data->protect_data);
		sem_unlink("/protect_data");
	}
	if (data->print_status != SEM_FAILED)
	{
		sem_close(data->print_status);
		sem_unlink("/print");
	}
	if (data->philo)
		free(data->philo);
}

int	ft_fork_failed(pid_t pid, t_data *data, int i)
{
	if (pid < 0)
	{
		printf("Failed : fork !\n");
		kill_all_process_failed_fork(data, i);
		cleanup_all_resources(data);
		return (0);
	}
	return (1);
}
