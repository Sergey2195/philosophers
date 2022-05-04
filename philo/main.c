/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:06:35 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/04 20:36:27 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checker_dead(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_p)
	{
		pthread_mutex_lock(&info->status_lte);
		if (ft_time() - info->phil[i]->lte > info->t_die)
		{
			print_event(5, info->phil[i], info);
			pthread_mutex_lock(&info->status_stop);
			info->stop_ind = 1;
			pthread_mutex_unlock(&info->status_stop);
			pthread_mutex_unlock(&info->status_lte);
			return (1);
		}
		pthread_mutex_unlock(&info->status_lte);
		i++;
	}
	return (0);
}

int	checker_fed(t_info *info)
{
	int	i;

	i = 0;
	if (info->n_to_win == -1)
		return (0);
	while (i < info->num_p)
	{
		pthread_mutex_lock(&info->status_lte);
		if (info->phil[i]->food_counter < info->n_to_win)
		{
			pthread_mutex_unlock(&info->status_lte);
			return (0);
		}
		pthread_mutex_unlock(&info->status_lte);
		i++;
	}
	pthread_mutex_lock(&info->status_stop);
	info->stop_ind = 1;
	pthread_mutex_unlock(&info->status_stop);
	return (1);
}

void	checker(t_info *info)
{
	while (1)
	{
		if (checker_dead(info))
			return ;
		if (checker_fed(info))
			return ;
	}
}

int	start_threads(t_info *info)
{
	int	i;

	i = 0;
	info->thr_id_arr = (pthread_t *)malloc(sizeof(pthread_t) * info->num_p);
	if (info->thr_id_arr == NULL)
		malloc_error();
	while (i < info->num_p)
	{
		if (pthread_create(&info->thr_id_arr[i], NULL,
				living, (void *)info->phil[i]) != 0)
			return (-1);
		i++;
	}
	checker(info);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (check_arg(argc, argv) == -1)
		exit(EXIT_FAILURE);
	info = NULL;
	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
		malloc_error();
	init_info(info, argc, argv);
	check_vars(*info);
	init_forks(info);
	init_mutex_status(info);
	init_phil(info);
	if (start_threads(info) == -1)
		pthread_error();
	before_end(info);
	return (EXIT_SUCCESS);
}
