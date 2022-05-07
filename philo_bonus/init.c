/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:29:51 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/07 13:44:19 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_info(t_info *info, int argc, char **argv)
{
	if (argc == 6)
	{
		info->n_to_win = ft_atoi(argv[5]);
		if (info->n_to_win < 0)
		{
			printf("Number of times each philosopher must eat error\n");
			exit(EXIT_FAILURE);
		}
	}
	else
		info->n_to_win = -1;
	info->num_p = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->died_ind = 0;
}

void	init_philo(t_info *info)
{
	int	i;

	i = info->num_p;
	while (--i >= 0)
	{
		info->philo[i].id = i;
		info->philo[i].info = info;
		info->philo[i].food_counter = 0;
		info->philo[i].lte = 0;
	}
}

int	init_semaph(t_info *info)
{
	sem_unlink("/p_forks");
	sem_unlink("/p_printing");
	sem_unlink("/lte_check");
	info->forks = sem_open("/p_forks", O_CREAT, S_IRWXU, info->num_p);
	info->printing = sem_open("/p_printing", O_CREAT, S_IRWXU, 1);
	info->lte_check = sem_open("/lte_check", O_CREAT, S_IRWXU, 1);
	if (info->forks == SEM_FAILED || info->printing == SEM_FAILED || info->lte_check == SEM_FAILED)
			return (-1);
	else
		return (0);
}