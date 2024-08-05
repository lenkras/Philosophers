/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-10 10:43:22 by epolkhov          #+#    #+#             */
/*   Updated: 2024-07-10 10:43:22 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_simul t_simul;

typedef struct s_philo
{
	int				id;
	int				num_of_meal;
	unsigned long	last_meal;
	int				start_to_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				*philo_died;
	t_simul			*main;
	pthread_t		thread;
	int				*start_simulation;
	pthread_mutex_t	*start_mutex;
	int r_fork;
	int l_fork;
} t_philo;

typedef struct s_simul
{
	long			num_of_philos;
	long			period_to_eat;
	long			period_to_sleep;
	unsigned long	period_to_die;
	long			meals_count;
	int				died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
	size_t			start_time;
} t_simul;

int		error_message(char *msg);
int		check_if_digit(char *argv);
int		check_args(char **argv);
long 	ft_atol(const char *str);
int		ft_usleep(t_philo *philo, size_t time);
size_t	current_time(void);
void	message(t_philo *philo, char *msg);
int		check_if_dead(t_philo *philo);
void	*philo_routine(void *arg);
void	*simul_monitor(void *arg);
void    free_all(t_simul *data);


#endif