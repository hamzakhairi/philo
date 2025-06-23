/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_program_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:19:23 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 15:49:09 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

void	cleanup_all_resources_main(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo)
	{
		while (i < data->counter)
		{
			if (data->philo[i].protect_philo != SEM_FAILED)
				sem_close(data->philo[i].protect_philo);
			if (data->philo[i].str)
			{
				sem_unlink(data->philo[i].str);
				free(data->philo[i].str);
			}
			i++;
		}
		free(data->philo);
		data->philo = NULL;
	}
	cleanup_all_resources(data);
}

void	wait_all_process_to_finishe(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->counter)
	{
		waitpid(data->philo[i].pid, NULL, 0);
		i++;
	}
	cleanup_all_resources_main(data);
}

void	kill_all_process(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->counter)
	{
		kill(data->philo[i].pid, SIGKILL);
		i++;
	}
}

void	wait_finished_meal(t_data *data)
{
	int		finished;
	int		status;
	pid_t	pid;

	finished = 0;
	while (finished < data->counter)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_all_process(data);
				break ;
			}
			else if (WEXITSTATUS(status) == 0)
				finished++;
		}
		else if (WIFSIGNALED(status))
			finished++;
	}
}

void	kill_all_process_failed_fork(t_data	*data, int counter)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		kill(data->philo[i].pid, SIGKILL);
		i++;
	}
}
