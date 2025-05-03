/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:51:40 by hkhairi           #+#    #+#             */
/*   Updated: 2025/05/02 16:35:45 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>  
#include <limits.h>

typedef struct s_data t_data;

typedef struct s_philo {
    int id;
    int state;
    int eat_count;
    long last_meal;
    pthread_mutex_t eat_count_mutex;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    t_data *data;
} t_philo;

struct s_data {
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int dead;
    long start_time;
    pthread_mutex_t *forks; //
    pthread_mutex_t print;
    pthread_mutex_t death;
    t_philo *philos; //
};

// #define malloc(size) NULL

// monitor 
// void checker_philo(t_data *data);

// philo life 
void *philo_life(void *arg);

// validation function
int	ft_atoi(const char *str);
int main_validation(int argc, char *argv[]);
int validation_number(t_data *data);

// errors
// void print(char *str);
// void print_num(int nbr);

// init philo
int init_data(t_data *data, int argc, char *argv[]);
int init_pthread_data(t_data *data);
int init_philo(t_data *data);


// philosophers utils 
long get_time();
void print_died_philo(t_data *data , int id);

#endif