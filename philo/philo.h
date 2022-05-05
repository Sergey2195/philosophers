/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:06:54 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/05 08:48:10 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_phil
{
	int				id;
	int				food_counter;
	long long		lte;
	int				right_f;
	int				left_f;
	struct s_info	*info;
}	t_phil;

typedef struct s_info
{
	int				num_p;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_to_win;
	int				stop_ind;
	long long		start_time;
	t_phil			**phil;
	pthread_mutex_t	*forks;
	pthread_mutex_t	status_write;
	pthread_mutex_t	status_stop;
	pthread_mutex_t	status_lte;
	pthread_t		*thr_id_arr;
}	t_info;

int			ft_atoi(const char *str);
int			check_arg(int argc, char **argv);
void		init_info(t_info *info, int argc, char **argv);
void		init_forks(t_info *info);
void		init_phil(t_info *info);
void		check_vars(t_info info);
void		*living(void *data);
void		pthread_error(void);
void		malloc_error(void);
long long	ft_time(void);
void		*living(void *data);
void		wait_phil(long long time);
void		print_event(int ind, t_phil *phil, t_info *info);
void		before_end(t_info *info);
void		thinking(t_phil *phil, t_info *info);
void		eating_odd(t_phil *phil, t_info *info);
void		eating_even(t_phil *phil, t_info *info);
void		sleeping(t_phil *phil, t_info *info);
void		init_mutex_status(t_info *info);
void		*solo_phil(void *data);
#endif