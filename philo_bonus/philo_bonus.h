/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:34:02 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/06 14:48:29 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				id;
	long long		lte;
	int				food_counter;
	struct s_info	*info;
	pthread_t		checker;
	pid_t			pid;
}	t_philo;

typedef struct s_info
{
	int				num_p;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_to_win;
	int				stop_ind;
	long long		start_time_all;
	t_philo			**philo;
	sem_t			*forks;
	sem_t			*printing;
	sem_t			*lte_check;
	sem_t			*stop_check;
}	t_info;

int			ft_atoi(const char *str);
int			check_arg(int argc, char **argv);
void		check_vars(t_info *info);
void		init_info(t_info *info, int argc, char **argv);
void		init_philo(t_info *info);
int			init_semaph(t_info *info);
void		pthread_error(void);
void		malloc_error(void);
void		fork_error(void);
void		wait_phil(long long time);
long long	ft_time(void);
void		start_living(t_philo *philo);
void		*checker(void *data);
void		print_action(int ind, t_philo *philo, t_info *info);
#endif