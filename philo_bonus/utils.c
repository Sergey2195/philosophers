/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:39:06 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/09 12:30:10 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_time(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

void	wait_phil(long long time)
{
	long long	c_time;

	c_time = ft_time();
	while (1)
	{
		if ((ft_time() - c_time) >= time)
			break ;
		usleep(50);
	}
}

void	*checker(void *data)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)data;
	info = philo->info;
	while (1)
	{
		time_to_die(info, philo);
		usleep(1000);
		if (fed_check(info, philo))
			break ;
	}
	return (NULL);
}
