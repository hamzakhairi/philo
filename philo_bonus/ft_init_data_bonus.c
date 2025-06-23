/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:37:53 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 14:26:10 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

int	ft_chek_sem_data(t_data *data)
{
	if (data->print_status == SEM_FAILED
		|| data->protect_data == SEM_FAILED)
	{
		printf("Failed : sem open !\n");
		return (0);
	}
	return (1);
}

int	creat_sem_for_data(t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	while (i < data->counter)
	{
		str = genret_name("forks_", i);
		if (!str)
			return (cleanup_fork_arrays(data, i), 0);
		sem_unlink(str);
		data->fork_each_ph[i] = sem_open(str, O_CREAT, 0644, 1);
		if (data->fork_each_ph[i] == SEM_FAILED)
			return (free(str), cleanup_fork_arrays(data, i), 0);
		data->name_forks[i] = ft_strdup(str);
		free(str);
		if (!data->name_forks[i])
		{
			sem_close(data->fork_each_ph[i]);
			cleanup_fork_arrays(data, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_fork_semaphores(t_data *data)
{
	int		i;

	i = 0;
	data->fork_each_ph = malloc(sizeof(sem_t *) * data->counter);
	if (!data->fork_each_ph)
		return (0);
	data->name_forks = malloc(sizeof(char *) * data->counter);
	if (!data->name_forks)
	{
		free(data->fork_each_ph);
		data->fork_each_ph = NULL;
		return (0);
	}
	while (i < data->counter)
	{
		data->fork_each_ph[i] = SEM_FAILED;
		data->name_forks[i] = NULL;
		i++;
	}
	creat_sem_for_data(data);
	return (1);
}

int	ft_init_data(t_data *data, int argc, char *argv[])
{
	if (!ft_check(argc, argv))
		return (0);
	data->counter = ft_atoi(argv[1]);
	data->time_died_ph = ft_atoi(argv[2]);
	data->time_eat_ph = ft_atoi(argv[3]);
	data->time_sleep_ph = ft_atoi(argv[4]);
	data->counter_must_eat = -1;
	if (argc == 6)
		data->counter_must_eat = ft_atoi(argv[5]);
	data->is_died = 0;
	data->time_start = get_time();
	data->finished_meals = 0;
	sem_unlink("/print");
	sem_unlink("/protect_data");
	sem_unlink("/finish_meal");
	if (!init_fork_semaphores(data))
		return (0);
	data->print_status = sem_open("/print", O_CREAT, 0644, 1);
	data->protect_data = sem_open("/protect_data", O_CREAT, 0644, 1);
	if (!ft_chek_sem_data(data))
		return (handel_faild(data, data->counter), 0);
	data->philo = malloc(sizeof(t_philo) * data->counter);
	if (!data->philo)
		return (handel_faild(data, data->counter), 0);
	return (1);
}
