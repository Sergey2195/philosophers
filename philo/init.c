/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:36:31 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/01 18:38:55 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_info *info)
{
	int	i;

	info->forks = NULL;
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->num_p);
	if (!info->forks)
		malloc_error();
	i = 0;
	while (i < info->num_p)
	{
		if (pthread_mutex_init(&info->forks[i], 0) != 0)
			pthread_error();
		i++;
	}
	if (pthread_mutex_init(&info->status_write, 0) != 0)
		pthread_error();
}

int	init_info(t_info *info, int argc, char **argv)
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
	info->dead_ind = 0;
	info->stop_ind = 0;
	info->start_time = ft_time();
	return (1);
}

void	init_phil(t_info *info)
{
	int	i;

	i = 0;
	info->phil = NULL;
	info->phil = (t_phil **)malloc(sizeof(t_phil *) * (info->num_p));
	if (info->phil == NULL)
		malloc_error();
	while (i < info->num_p)
	{
		info->phil[i] = (t_phil *)malloc(sizeof(t_phil));
		if (info->phil[i] == NULL)
			malloc_error();
		info->phil[i]->id = i;
		info->phil[i]->info = info;
		info->phil[i]->food_counter = 0;
		info->phil[i]->lte = ft_time();
		info->phil[i]->left_f = i;
		info->phil[i]->stop_ind = 0;
		if (i == 0)
			info->phil[i]->right_f = info->num_p - 1;
		else
			info->phil[i]->right_f = i - 1;
		i++;
	}
}
