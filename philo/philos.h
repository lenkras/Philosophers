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

#ifndef PHILOS_H
# define PHILOS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_simul	t_simul;

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
}	t_philo;

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
	pthread_mutex_t	start_mutex;
	int				start_simulation;
}	t_simul;

int		init_simulation(t_simul *data, char **argv, int argc);
int		init_arguments(t_simul *info, char **argv, int argc);
int		init_philos(t_simul *data);
int		init_data(t_simul *data);
int		init_mutex_forks(t_simul *data);
int		init_mutex_locks(t_simul *data);
int		error_message(char *msg);
int		check_if_digit(char *argv);
int		check_args(char **argv);
long	ft_atol(const char *str);
int		ft_usleep(t_philo *philo, size_t time);
size_t	current_time(void);
void	message(t_philo *philo, char *msg);
int		check_if_dead(t_philo *philo);
void	*philo_routine(void *arg);
void	*simul_monitor(void *arg);
void	free_all(t_simul *data);
int		create_threads(t_simul *data);
void	check_if_simul_start(t_philo *philo);
void	philo_eat(t_philo *philo);
int		ft_strlen(char *str);

#endif
