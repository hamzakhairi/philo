/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation_data_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:41:33 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/05 09:24:11 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
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
		if (!ft_isdigit(str[i]))
			return (0);
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check(int argc, char *argv[])
{
	if (!ft_input_validation(argv[1])
		|| !ft_input_validation(argv[2])
		|| !ft_input_validation(argv[3])
		|| !ft_input_validation(argv[4]))
		return (0);
	if (argc == 6 && !ft_input_validation(argv[5]))
		return (0);
	return (1);
}
