/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:06:54 by iannmari          #+#    #+#             */
/*   Updated: 2022/05/01 18:58:08 by iannmari         ###   ########.fr       */
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
	int				stop_ind;
	struct s_info	*info;
}	t_phil;

typedef struct s_info
{
	int				num_p;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_to_win;
	int				dead_ind;
	int				stop_ind;
	long long		start_time;
	t_phil			**phil;
	pthread_mutex_t	*forks;
	pthread_mutex_t	status_write;
	pthread_t		*thr_id_arr;
	pthread_t		checker;
}	t_info;

int			ft_atoi(const char *str);
int			check_arg(int argc, char **argv);
int			init_info(t_info *info, int argc, char **argv);
void		init_forks(t_info *info);
void		init_phil(t_info *info);
void		check_vars(t_info info);
void		*living(void *data);
void		pthread_error(void);
void		malloc_error(void);
long long	ft_time(void);
void		check_death(t_info *info);
void		*living(void *data);
void		wait_phil(long long time);
void		print_event(int ind, t_phil *phil, t_info *info);
void		before_end(t_info *info);
#endif