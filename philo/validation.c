/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:04:06 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/02 23:00:07 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validation_number(t_data *data)
{
	if (data->num_philos < 1)
	{
		free(data->philos);
		printf("Failed argument !\n");
		return (0);
	}
	return (1);
}

int	validation_integer(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error parsing : invalid argument\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_input_validation(char *str)
{
	unsigned long long	num;
	int					i;

	num = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

void	print_error(void)
{
	printf("Usage : ./philo  \n --> [number_of_philosophers]\n");
	printf(" --> [time_to_die]\n");
	printf(" --> [time_to_eat]\n --> [time_to_sleep]\n -->");
	printf(" [number_of_times_each_philosopher_must_eat]\n");
}

int	main_validation(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc > 6 || argc < 5)
	{
		print_error();
		return (0);
	}
	if (!validation_integer(argc, argv))
		return (0);
	while (i < argc)
	{
		if (!ft_input_validation(argv[i]))
		{
			printf("Error parsing : invalid argument\n");
			return (0);
		}
		i++;
	}
	return (1);
}
