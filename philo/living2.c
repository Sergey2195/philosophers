/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:13:47 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/03 15:21:57 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	thinking(t_phil *phil, t_info *info)
{
	print_event(4, phil, info);
}
