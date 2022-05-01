/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:18:18 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/01 22:14:58 by iannmari         ###   ########.fr       */
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

void	sleeping(t_phil *phil, t_info *info)
{
	print_event(3, phil, info);
	wait_phil(info->t_sleep);
}

void	eating_even(t_phil *phil, t_info *info)
{
	pthread_mutex_lock(&info->forks[phil->right_f]);
	print_event(1, phil, info);
	pthread_mutex_lock(&info->forks[phil->left_f]);
	print_event(0, phil, info);
	phil->food_counter++;
	phil->lte = ft_time();
	print_event(2, phil, info);
	wait_phil(info->t_eat);
	pthread_mutex_unlock(&info->forks[phil->left_f]);
	pthread_mutex_unlock(&info->forks[phil->right_f]);
}

void	eating_odd(t_phil *phil, t_info *info)
{
	pthread_mutex_lock(&info->forks[phil->left_f]);
	print_event(0, phil, info);
	pthread_mutex_lock(&info->forks[phil->right_f]);
	print_event(1, phil, info);
	phil->food_counter++;
	phil->lte = ft_time();
	print_event(2, phil, info);
	wait_phil(info->t_eat);
	pthread_mutex_unlock(&info->forks[phil->left_f]);
	pthread_mutex_unlock(&info->forks[phil->right_f]);
}

void	*living(void *data)
{
	t_phil	*phil;
	t_info	*info;

	phil = (t_phil *)data;
	info = phil->info;
	while (1)
	{
		if (info->stop_ind || phil->food_counter >= info->n_to_win)
			return (NULL);
		if ((phil->id % 2 == 0) && phil->id + 1 != info->num_p)
			eating_even(phil, info);
		else
			eating_odd(phil, info);
		if (info->stop_ind)
			return (NULL);
		sleeping(phil, info);
		if (info->stop_ind)
			return (NULL);
		print_event(4, phil, info);
	}
	return (NULL);
}
