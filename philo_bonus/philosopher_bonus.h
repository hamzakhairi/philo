/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:46:53 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/10 15:10:17 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		id;
	int		eat_count;
	long	last_meal;
	pid_t	pid;
	t_data	*data;
	sem_t	*protect_philo;
	char	*str;
	int		first_fork;
	int		second_fork;
}	t_philo;

struct s_data
{
	int		counter;
	long	time_died_ph;
	long	time_eat_ph;
	long	time_sleep_ph;
	int		counter_must_eat;
	long	time_start;
	int		is_died;
	sem_t	**fork_each_ph;
	sem_t	*print_status;
	char	**name_forks;
	int		finished_meals;
	t_philo	*philo;
	sem_t	*protect_data;
};

int		ft_strlen(char *str);
int		ft_main_validation(int argc, char *argv[]);
int		ft_check(int argc, char *argv[]);
int		ft_init_data(t_data *data, int argc, char *argv[]);
int		ft_init_philo(t_data *data);
void	philo_life(t_philo *philo);
int		ft_atoi(char *str);
long	get_time(void);
char	*genret_name(char *str, int index);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
int		check_last_meal(t_philo *philo);
void	print_status(t_philo *philo, char *status, int keep_lock);
void	*death_check(void *arg);
void	ft_usleep(t_philo *philo, long duration);
char	*ft_strdup(char *s);
int		check_death(t_philo *philo);
void	set_died(t_philo *philo);
void	cleanup_fork_each_philo(t_data *data);
void	cleanup_name_fork(t_data *data);
void	cleanup_all_resources(t_data *data);
void	cleanup_fork_philo_index(t_data *data, int count);
void	cleanup_name_fork_index(t_data *data, int count);
void	cleanup_fork_arrays(t_data *data, int count);
void	cleanup_semaphores(t_data *data);
void	handel_faild(t_data *data, int fork_count);
int		ft_fork_failed(pid_t pid, t_data *data, int i);
void	cleanup_all_resources_main(t_data *data);
void	wait_all_process_to_finishe(t_data	*data);
void	kill_all_process(t_data	*data);
void	wait_finished_meal(t_data	*data);
void	check_counter_meals(t_philo *philo);
void	kill_all_process_failed_fork(t_data	*data, int counter);

#endif