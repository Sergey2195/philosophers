/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:32:02 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/09 12:29:49 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_sem(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->printing);
	sem_close(info->lte_check);
	sem_close(info->dead_check);
	sem_unlink("p_forks");
	sem_unlink("p_printing");
	sem_unlink("lte_check");
	sem_unlink("dead_check");
}

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
			i = 0;
			while (i < info->num_p)
			{	
				kill(info->philo[i].pid, SIGTERM);
				i++;
			}
			break ;
		}
		i++;
	}
	close_sem(info);
}

void	start_sim(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = info->philo;
	info->start_time_all = ft_time();
	while (i < info->num_p)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			fork_error();
		if (philo[i].pid == 0)
			start_living(&(philo[i]));
		i++;
	}
	exit_info(info);
}

void	action_print(t_info *info, int id, char *string)
{
	sem_wait(info->printing);
	if (!info->died_ind)
		printf("%lld %d %s\n", ft_time() - info->start_time_all, id + 1, string);
	sem_post(info->printing);
}

int	main(int argc, char **argv)
{
	t_info	info;

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
