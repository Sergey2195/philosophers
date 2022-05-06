/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:40:02 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/06 20:24:42 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleep_philo(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	print_action(2, philo, info);
	wait_phil(info->t_sleep);
}

void	eating(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	sem_wait(info->forks);
	print_action(0, philo, info);
	sem_wait(info->forks);
	print_action(0, philo, info);
	print_action(1, philo, info);
	sem_wait(info->lte_check);
	philo->lte = ft_time();
	philo->food_counter++;
	sem_post(info->lte_check);
	wait_phil(info->t_eat);
	sem_post(info->forks);
	sem_post(info->forks);
}

void	*checker(void *data)
{
	t_philo		*philo;
	int			ind;

	philo = (t_philo *)data;
	ind = 0;
	while (1)
	{
		sem_wait(philo->info->lte_check);
		if (ft_time() - philo->lte > philo->info->t_die)
		{
			print_action(4, philo, philo->info);
			sem_wait(philo->info->stop_check);
			philo->info->stop_ind = 1;
			sem_wait(philo->info->printing);
			sem_post(philo->info->stop_check);
			sem_post(philo->info->lte_check);
			break ;
		}
		if (philo->food_counter >= philo->info->n_to_win && philo->info->n_to_win != -1)
		{
			sem_wait(philo->info->stop_check);
			philo->info->stop_ind = 1;
			sem_post(philo->info->stop_check);
			sem_post(philo->info->lte_check);
			break ;
		}
		sem_post(philo->info->lte_check);
		usleep(1000);
	}
	return (NULL);
}

int	check_continuation(t_philo *philo)
{
	sem_wait(philo->info->stop_check);
	if (philo->info->stop_ind)
	{
		sem_post(philo->info->stop_check);
		return (1);
	}
	sem_post(philo->info->stop_check);
	return (0);
}

void	start_living(t_philo *philo)
{
	philo->lte = ft_time();
	if (pthread_create(&philo->checker, NULL, checker, (void *)philo) != 0)
	{
		pthread_error();
		return ;
	}
	while (1)
	{
		if (check_continuation(philo))
			break ;
		eating(philo);
		if (check_continuation(philo))
			break ;
		sleep_philo(philo);
		if (check_continuation(philo))
			break ;
		print_action(3, philo, philo->info);
	}
	pthread_join(philo->checker, NULL);
	sem_wait(philo->info->stop_check);
	if (philo->info->stop_ind)
	{
		sem_post(philo->info->stop_check);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}