/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:40:02 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/07 14:22:51 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	sleep_philo(t_philo *philo)
// {
// 	t_info	*info;

// 	info = philo->info;
// 	print_action(2, philo, info);
// 	wait_phil(info->t_sleep);
// }

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

void	*checker(void *data)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)data;
	info = philo->info;
	while (42)
	{
		sem_wait(info->lte_check);
		if (ft_time() - philo->lte > info->t_die)
		{
			action_print(info, philo->id, "died");
			info->died_ind = 1;
			sem_wait(info->printing);
			exit(1);
		}
		sem_post(info->lte_check);
		if (info->died_ind) //data races?
			break ;
		usleep(1000);
		if (philo->food_counter >= info->n_to_win && info->n_to_win != -1) //data races?
			break ;
	}
	return (NULL);
}

// int	check_continuation(t_philo *philo)
// {
// 	sem_wait(philo->info->stop_check);
// 	if (philo->info->stop_ind)
// 	{
// 		sem_post(philo->info->stop_check);
// 		return (1);
// 	}
// 	sem_post(philo->info->stop_check);
// 	return (0);
// }

int	died_check(t_info *info)
{
	sem_wait(info->lte_check);
	if (info->died_ind)
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
	while (!(info->died_ind))
	{
		eating(philo);
		if (philo->food_counter >= info->n_to_win && info->n_to_win != -1)
			break ;
		action_print(info, philo->id, "is sleeping");
		wait_phil(info->t_sleep, info);
		action_print(info, philo->id, "is thinking");
	}
	pthread_join(philo->checker, NULL);
	if (died_check(info))
		exit(1);
	exit(0);
}