/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:21:50 by hkhairi           #+#    #+#             */
/*   Updated: 2025/06/05 09:53:48 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher_bonus.h"

static int	len_of_number(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static unsigned int	n_to_nbr(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	int				len_nbr;
	char			*res;
	unsigned int	nbr;

	len_nbr = len_of_number(n);
	res = (char *)malloc(sizeof(char) * (len_nbr + 1));
	if (!res)
		return (NULL);
	res[len_nbr] = '\0';
	if (n < 0)
		res[0] = '-';
	nbr = n_to_nbr(n);
	while (len_nbr-- > 0 && nbr != 0)
	{
		if (len_nbr == 0 && n < 0)
			break ;
		res[len_nbr] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n == 0)
		res[0] = '0';
	return (res);
}
