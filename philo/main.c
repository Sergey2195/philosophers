/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:06:35 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/01 22:34:07 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	everyone_is_fed(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_p)
	{
		if (info->phil[i]->food_counter < info->n_to_win)
			return (0);
		i++;
	}
	return (1);
}

int	check_philo(t_info	*info)
{
	int			i;
	long long	curr_time;

	i = 0;
	while (i < info->num_p)
	{
		curr_time = ft_time();
		if (info->n_to_win != -1)
		{
			if (everyone_is_fed(info))
			{
				info->stop_ind = 1;
				return (1);
			}	
		}
		if (curr_time - info->phil[i]->lte > info->t_die && info->phil[i]->food_counter < info->n_to_win)
		{
			print_event(5, info->phil[i], info);
			info->stop_ind = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	*checker(void *data)
{
	t_info		*info;

	info = (t_info *)data;
	while (1)
	{
		if (check_philo(info))
			break ;
	}
	return (NULL);
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
	if (pthread_create(&info->checker, NULL, checker, (void *)info) != 0)
		return (-1);
	pthread_join(info->checker, NULL);
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
	init_phil(info);
	if (start_threads(info) == -1)
		pthread_error();
	before_end(info);
	return (EXIT_SUCCESS);
}
