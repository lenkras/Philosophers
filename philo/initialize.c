/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-09 14:41:42 by epolkhov          #+#    #+#             */
/*   Updated: 2024-08-09 14:41:42 by epolkhov         ###   ########.fr       */
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
		if (check_if_digit(argv[5]) || ft_strlen(argv[5]) > 7)
			return (error_message
				("Invalid number of times each philo must eat"));
		info->meals_count = ft_atol(argv[5]);
		if (info->meals_count < 0)
		{
			return (error_message
				("Invalid number of times each philo must eat"));
		}
	}
	else
		info->meals_count = -1;
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

static void	init_data(t_simul *data)
{
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
}

static int	init_mutex(t_simul *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			error_message("Mutex initialization failed");
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			free(data->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_simulation(t_simul *data, char **argv, int argc)
{
	if (init_arguments(data, argv, argc))
		return (1);
	init_data(data);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	data->start_simulation = 0;
	if (init_mutex(data))
		return (1);
	init_philos(data);
	return (0);
}
