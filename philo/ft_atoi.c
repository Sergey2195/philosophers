/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:10:40 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/04 19:49:45 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_num(char *str, int z)
{
	long long	i;
	long long	k;

	i = 0;
	k = 0;
	while (str[i] > 47 && str[i] < 58)
	{
		k = k * 10 + (str[i] - 48);
		i++;
	}
	if (z == 1)
		k = -k;
	return (k);
}

int	ft_atoi(const char *str)
{
	long long	i;
	long long	z;
	long long	y;

	i = 0;
	z = 0;
	y = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			z = 1;
		i++;
	}
	if (str[i] > 47 && str[i] < 58)
	{
		y = ft_num((char *)str + i, z);
		if (y > 2147483647 || y < -2147483648)
			y = -1;
		return ((int)y);
	}
	return ((int)y);
}
