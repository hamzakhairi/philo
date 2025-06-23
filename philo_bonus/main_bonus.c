/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:28:46 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 14:48:07 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

void	wait_philo(t_data *data)
{
	int		status;
	int		i;
	pid_t	pid;

	i = 0;
	if (data->counter_must_eat != -1)
	{
		wait_finished_meal(data);
	}
	else
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			kill_all_process(data);
	}
	cleanup_all_resources_main(data);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	data.fork_each_ph = NULL;
	data.name_forks = NULL;
	data.philo = NULL;
	data.print_status = SEM_FAILED;
	data.protect_data = SEM_FAILED;
	if (!ft_main_validation(argc, argv))
		return (1);
	if (!ft_init_data(&data, argc, argv))
	{
		cleanup_all_resources_main(&data);
		return (1);
	}
	if (!ft_init_philo(&data))
	{
		cleanup_all_resources_main(&data);
		return (1);
	}
	wait_philo(&data);
	return (0);
}
