/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:24:06 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/01 18:37:20 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pthread_error(void)
{
	printf("pthread_mutex_init error\n");
	exit(EXIT_FAILURE);
}

void	malloc_error(void)
{
	printf("Malloc error\n");
	exit(EXIT_FAILURE);
}
