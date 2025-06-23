/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:32:53 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 15:10:03 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

int	creat_philo_prosses(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->counter)
	{
		data->philo[i].pid = fork();
		if (!ft_fork_failed(data->philo[i].pid, data, i))
			return (0);
		if (data->philo[i].pid == 0)
		{
			philo_life(&data->philo[i]);
			exit(0);
		}
		i++;
	}
	return (1);
}

void	cleanup_philo_semaphores(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (data->philo[i].protect_philo != SEM_FAILED)
			sem_close(data->philo[i].protect_philo);
		if (data->philo[i].str)
		{
			sem_unlink(data->philo[i].str);
			free(data->philo[i].str);
			data->philo[i].str = NULL;
		}
		i++;
	}
}

void	destroy_philo(t_data *data, int index, int from_sem_open)
{
	if (from_sem_open && data->philo[index].str)
		free(data->philo[index].str);
	cleanup_philo_semaphores(data, index);
	cleanup_all_resources(data);
}

int	init_philo(t_data *data, int i)
{
	char	*str;
	int		tmp;

	data->philo[i].second_fork = (i + 1) % data->counter;
	if (i % 2 == 1)
	{
		tmp = data->philo[i].first_fork;
		data->philo[i].first_fork = data->philo[i].second_fork;
		data->philo[i].second_fork = tmp;
	}
	str = genret_name("/protect_philo_", i);
	if (!str)
		return (printf("Failed : memory allocation for semaphore name!\n"),
			destroy_philo(data, i, 0), 0);
	sem_unlink(str);
	data->philo[i].str = str;
	data->philo[i].protect_philo = sem_open(str, O_CREAT, 0644, 1);
	if (data->philo[i].protect_philo == SEM_FAILED)
	{
		printf("Failed : open semaphore for philosopher %d!\n", i + 1);
		destroy_philo(data, i, 1);
		return (0);
	}
	return (1);
}

int	ft_init_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->counter)
	{
		data->philo[i].protect_philo = SEM_FAILED;
		data->philo[i].str = NULL;
		i++;
	}
	i = 0;
	while (i < data->counter)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].data = data;
		data->philo[i].first_fork = i;
		if (!init_philo(data, i))
			return (0);
		i++;
	}
	if (!creat_philo_prosses(data))
		return (0);
	return (1);
}
