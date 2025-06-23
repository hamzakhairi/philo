/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_life_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:28:47 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 14:50:34 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

void	unlock_forks(t_philo *philo)
{
	sem_post(philo->data->fork_each_ph[philo->second_fork]);
	sem_post(philo->data->fork_each_ph[philo->first_fork]);
}

int	handle_forks(t_philo *philo)
{
	sem_wait(philo->data->fork_each_ph[philo->second_fork]);
	if (check_death(philo))
	{
		sem_post(philo->data->fork_each_ph[philo->second_fork]);
		return (0);
	}
	print_status(philo, "has taken a fork", 0);
	sem_wait(philo->data->fork_each_ph[philo->first_fork]);
	if (check_death(philo))
	{
		sem_post(philo->data->fork_each_ph[philo->second_fork]);
		sem_post(philo->data->fork_each_ph[philo->first_fork]);
		return (0);
	}
	print_status(philo, "has taken a fork", 0);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	int	eat_count;
	int	must_eat;

	if (!handle_forks(philo))
		return (0);
	if (check_death(philo))
		return (unlock_forks(philo), 0);
	sem_wait(philo->protect_philo);
	philo->last_meal = get_time();
	sem_post(philo->protect_philo);
	print_status(philo, "is eating", 0);
	ft_usleep(philo, philo->data->time_eat_ph);
	unlock_forks(philo);
	if (check_death(philo))
		return (0);
	sem_wait(philo->protect_philo);
	philo->eat_count += 1;
	eat_count = philo->eat_count;
	sem_post(philo->protect_philo);
	sem_wait(philo->data->protect_data);
	must_eat = philo->data->counter_must_eat;
	sem_post(philo->data->protect_data);
	if (must_eat != -1 && eat_count >= must_eat)
		return (check_counter_meals(philo), 0);
	return (1);
}

void	philo_life(t_philo *philo)
{
	pthread_t	monitor;

	if (philo->data->counter_must_eat == 0)
		exit(0);
	if (philo->data->time_died_ph == 0)
		exit(0);
	philo->last_meal = philo->data->time_start;
	pthread_create(&monitor, NULL, death_check, philo);
	pthread_detach(monitor);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!philo_eat(philo))
			exit(0);
		if (check_death(philo))
			exit(1);
		print_status(philo, "is sleeping", 0);
		ft_usleep(philo, philo->data->time_sleep_ph);
		if (check_death(philo))
			exit(1);
		print_status(philo, "is thinking", 0);
	}
	exit (0);
}

void	*death_check(void *arg)
{
	t_philo	*philo;
	int		eat_count;
	int		must_eat;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_last_meal(philo))
		{
			(print_status(philo, "died", 1),
				set_died(philo), exit(1));
		}
		if (check_death(philo))
			break ;
		sem_wait(philo->protect_philo);
		eat_count = philo->eat_count;
		sem_post(philo->protect_philo);
		sem_wait(philo->data->protect_data);
		must_eat = philo->data->counter_must_eat;
		sem_post(philo->data->protect_data);
		if (must_eat != -1 && eat_count >= must_eat)
			break ;
		usleep(1000);
	}
	return (NULL);
}
