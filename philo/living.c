/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:18:18 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/05 08:52:40 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*solo_phil(void *data)
{
	t_info	*info;

	info = (t_info *)data;
	wait_phil(info->t_die);
	print_event(5, info->phil[0], info);
	return (NULL);
}

int	check_stop(t_info *info)
{
	pthread_mutex_lock(&info->status_stop);
	if (info->stop_ind)
	{
		pthread_mutex_unlock(&info->status_stop);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&info->status_stop);
		return (0);
	}
}

void	print_event(int ind, t_phil *phil, t_info *info)
{
	long long	current_time;

	current_time = ft_time() - info->start_time;
	pthread_mutex_lock(&info->status_write);
	pthread_mutex_lock(&info->status_stop);
	if (info->stop_ind)
	{
		pthread_mutex_unlock(&info->status_stop);
		pthread_mutex_unlock(&info->status_write);
		return ;
	}
	pthread_mutex_unlock(&info->status_stop);
	if (ind == 0)
		printf("%lld %d has taken a fork\n", current_time, phil->id + 1);
	if (ind == 1)
		printf("%lld %d has taken a fork\n", current_time, phil->id + 1);
	if (ind == 2)
		printf("%lld %d is eating\n", current_time, phil->id + 1);
	if (ind == 3)
		printf("%lld %d is sleeping\n", current_time, phil->id + 1);
	if (ind == 4)
		printf("%lld %d is thinking\n", current_time, phil->id + 1);
	if (ind == 5)
		printf("%lld %d died\n", current_time, phil->id + 1);
	pthread_mutex_unlock(&info->status_write);
}

void	*living(void *data)
{
	t_phil	*phil;
	t_info	*info;

	phil = (t_phil *)data;
	info = phil->info;
	while (1)
	{
		if (check_stop(info))
			return (NULL);
		if ((phil->id % 2 == 0) && phil->id + 1 != info->num_p)
			eating_even(phil, info);
		else
			eating_odd(phil, info);
		if (check_stop(info))
			return (NULL);
		sleeping(phil, info);
		if (check_stop(info))
			return (NULL);
		thinking(phil, info);
	}
	return (NULL);
}
