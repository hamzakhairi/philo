/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:51:40 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 14:17:13 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>  
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	size_t			last_meal;
	pthread_mutex_t	eat_count_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

struct	s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				dead;
	int				is_full;
	long			start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	t_philo			*philos;
};

void	*philo_life(void *arg);
int		ft_atoi(const char *str);
int		main_validation(int argc, char *argv[]);
int		validation_number(t_data *data);
int		init_data(t_data *data, int argc, char *argv[]);
int		init_pthread_data(t_data *data);
int		init_philo(t_data *data);
long	get_time(void);
void	print_died_philo(t_data *data, int id);
int		get_dead(t_data *data);
void	set_dead(t_data *data, int value);
void	print_died_philo(t_data *data, int id);
void	print_status(t_philo *philo, char *msg);
void	update_last_meal(t_philo *philo);
int		check_death(t_philo *philo);
void	ft_usleep(t_philo *philo, long duration);

#endif