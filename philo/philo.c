/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-10 10:42:00 by epolkhov          #+#    #+#             */
/*   Updated: 2024-07-10 10:42:00 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	init_arguments(t_simul *info, char **argv, int argc)
{
	info->num_of_philos = ft_atol(argv[1]);
	info->period_to_die = ft_atol(argv[2]);
	info->period_to_eat = ft_atol(argv[3]);
	info->period_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		info->meals_count = ft_atol(argv[5]);
		if (info->meals_count < 0)
		{
			return (error_message("Invalid number of times each philosopher must eat"));
		}
	}
	else
		info->meals_count = 0;
	return (0);
}

static int	init_philos(t_simul *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].num_of_meal = 0;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->num_of_philos];
		data->philos[i].philo_died = &data->died;
		data->philos[i].main = data;
		data->philos[i].last_meal = current_time();
		i++;
	}
	return (0);
}

 static void	init_simulation(t_simul *data, char **argv, int argc)
{
	int	i;

	i = 0;
	if (init_arguments(data, argv, argc))
		return ;
	data->died = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return ;
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
	{
		free(data->forks);
		return ;
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philos(data);
}

int	create_threads(t_simul *data)
{
	int				i;
	pthread_t		monitor;
	pthread_mutex_t	start_mutex;
	int				start_simul;

	i = 0;
	start_simul = 0;
	pthread_mutex_init(&start_mutex, NULL);
	data->start_time = current_time();
	if (pthread_create(&monitor, NULL, &simul_monitor, data) != 0)
		return (error_message("Failed to create monitor thread"));
	while (i < data->num_of_philos)
	{
		printf("Create thread %d\n", i);
		data->philos[i].start_simulation = &start_simul;
		data->philos[i].start_mutex = &start_mutex;
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, \
				&data->philos[i]) != 0)
			return (error_message("Failed to create thread"));
		i++;
	}
	pthread_mutex_lock(&start_mutex);
	start_simul = 1;
	pthread_mutex_unlock(&start_mutex);
	if (pthread_join(monitor, NULL) != 0)
		return (error_message("Failed to join monitor thread"));
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (error_message("Failed to join threads"));
		i++;
	}
	pthread_mutex_destroy(&start_mutex);
	return (0);
}

int	main (int argc, char **argv)
{
	t_simul		data;
	
	if (argc < 5 || argc > 6)
		return (error_message("Invalid number of arguments"));
	if (check_args(argv))
		return (1);
	init_simulation(&data, argv, argc);
	if (create_threads(&data))
	{
		free_all(&data);
		return (1);
	}
	free_all(&data);
	return (0);
}
