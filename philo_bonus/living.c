/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:40:02 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/07 16:57:50 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	sem_wait(info->forks);
	action_print(info, philo->id, "has taken a fork");
	sem_wait(info->forks);
	action_print(info, philo->id, "has taken a fork");
	sem_wait(info->lte_check);
	action_print(info, philo->id, "is eating");
	philo->lte = ft_time();
	philo->food_counter++;
	sem_post(info->lte_check);
	wait_phil(info->t_eat, info);
	sem_post(info->forks);
	sem_post(info->forks);
}

void	time_to_die(t_info *info, t_philo *philo)
{
	sem_wait(info->lte_check);
	if (ft_time() - philo->lte > info->t_die)
	{
		action_print(info, philo->id, "died");
		sem_wait(info->dead_check);
		info->died_ind = 1;
		sem_post(info->dead_check);
		sem_post(info->lte_check);
		sem_wait(info->printing);
		exit(1);
	}
	sem_post(info->lte_check);
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

int	died_check(t_info *info)
{
	sem_wait(info->dead_check);
	if (info->died_ind)
	{
		sem_post(info->dead_check);
		return (1);
	}
	sem_post(info->dead_check);
	return (0);
}

int	fed_check(t_info *info, t_philo *philo)
{
	sem_wait(info->lte_check);
	if (info->n_to_win != -1 && philo->food_counter >= info->n_to_win)
	{
		sem_post(info->lte_check);
		return (1);
	}
	sem_post(info->lte_check);
	return (0);
}

void	start_living(void *data)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)data;
	info = philo->info;
	philo->lte = ft_time();
	pthread_create(&(philo->checker), NULL, checker, data);
	if (philo->id % 2)
		usleep(10000);
	while (1)
	{
		eating(philo);
		if (died_check(info) || fed_check(info, philo))
			break ;
		action_print(info, philo->id, "is sleeping");
		wait_phil(info->t_sleep, info);
		action_print(info, philo->id, "is thinking");
		if (died_check(info))
			break ;
	}
	pthread_join(philo->checker, NULL);
	if (died_check(info))
		exit(1);
	exit(0);
}