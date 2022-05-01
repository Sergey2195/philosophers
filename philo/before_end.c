/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:12:09 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/01 18:37:07 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_free(t_info *info)
{
	int	i;

	i = 0;
	free(info->thr_id_arr);
	while (i < info->num_p)
	{
		free(info->phil[i]);
		i++;
	}
	free(info->phil);
	free(info->forks);
	free(info);
}

void	before_end(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_p)
	{
		pthread_join(info->thr_id_arr[i], NULL);
		i++;
	}
	i = 0;
	while (i < info->num_p)
	{
		pthread_mutex_unlock(&info->forks[i]);
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_unlock(&info->status_write);
	pthread_mutex_destroy(&info->status_write);
	all_free(info);
}
