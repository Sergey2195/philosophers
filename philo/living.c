/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:18:18 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/03 15:15:48 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_event(int ind, t_phil *phil, t_info *info)
{
	long long	current_time;

	if (info->stop_ind)
		return ;
	current_time = ft_time() - info->start_time;
	pthread_mutex_lock(&info->status_write);
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

int	living_cycle(t_phil *phil, t_info *info)
{
	if (info->stop_ind || (phil->food_counter >= info->n_to_win
			&& info->n_to_win != -1))
		return (1);
	if ((phil->id % 2 == 0) && phil->id + 1 != info->num_p)
		eating_even(phil, info);
	else
		eating_odd(phil, info);
	if (info->stop_ind)
		return (1);
	sleeping(phil, info);
	if (info->stop_ind)
		return (1);
	thinking(phil, info);
	return (0);
}

void	*living(void *data)
{
	t_phil	*phil;
	t_info	*info;

	phil = (t_phil *)data;
	info = phil->info;
	if (info->num_p == 1)
	{
		wait_phil(info->t_die);
		return (NULL);
	}
	while (1)
	{
		if (living_cycle(phil, info))
			return (NULL);
	}
	return (NULL);
}
