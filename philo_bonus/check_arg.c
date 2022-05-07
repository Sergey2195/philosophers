/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:30:40 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/07 16:26:43 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > '9' || str[i] < '0') && str[i] != '+' && str[i] != '-')
			return (-1);
		i++;
	}
	return (1);
}

int	check_arg(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		printf("Invalid number of arguments\n");
		return (-1);
	}
	argc -= 1;
	while (argc > 0)
	{
		if (check_numeric(argv[argc]) == -1)
		{
			printf("Invalid arguments\n");
			return (-1);
		}
		argc -= 1;
	}
	return (1);
}

void	check_vars(t_info *info)
{
	if (info->num_p <= 0 || info->t_sleep < 0 || info->t_eat < 0 || info->t_die < 0)
	{
		printf("Problem with args value\n");
		exit(EXIT_FAILURE);
	}
	if (info->n_to_win == 0)
	{
		exit(EXIT_SUCCESS);
	}
}
