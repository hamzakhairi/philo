/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:14:57 by hkhairi           #+#    #+#             */
/*   Updated: 2025/04/28 17:40:12 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

void put_char(char c)
{
    write(1, &c, 1);
}

void print_num(int nbr)
{
    if (nbr < 0)
    {
        put_char('-');
        print_num(nbr * -1);
    }
    else if (nbr > 9)
    {
        print_num(nbr / 10);
        print_num(nbr % 10);
    }
    else
    {
        put_char(nbr + '0');
    }
}
