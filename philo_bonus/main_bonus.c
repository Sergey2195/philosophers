/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:32:02 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/07 14:56:21 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_info(t_info *info)
{
	int	i;
	int	result;

	i = 0;
	while (i < info->num_p)
	{
		waitpid(-1, &result, 0);
		if (result != 0)
		{
			i = -1;
			while (++i < info->num_p)
				kill(info->philo[i].pid, 15);
			break ;
		}
		i++;
	}
	sem_close(info->forks);
	sem_close(info->printing);
	sem_close(info->lte_check);
	sem_unlink("/p_forks");
	sem_unlink("/p_printing");
	sem_unlink("/lte_check");
}

void	start_sim(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = info->philo;
	info->start_time_all = ft_time();
	while (++i < info->num_p)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			fork_error();
		if (philo[i].pid == 0)
			start_living(&(philo[i]));
	}
	exit_info(info);
	return ;
}

void	action_print(t_info *info, int id, char *string)
{
	sem_wait(info->printing);
	printf("%lld %d %s\n", ft_time() - info->start_time_all, id + 1, string);
	sem_post(info->printing);
	return ;
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		exit(0);
	if (check_arg(argc, argv) == -1)
		exit(EXIT_FAILURE);
	init_info(&info, argc, argv);
	check_vars(&info);
	init_philo(&info);
	if (init_semaph(&info) == -1)
		return (-1);
	start_sim(&info);
	return (0);
}