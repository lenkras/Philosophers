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

int	init_arguments(t_simul *info, char **argv, int argc)
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

int	init_philos(t_simul *data)
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

int	init_data(t_simul *data)
{
	data->died = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (error_message("Malloc failed"));
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
	{
		free(data->forks);
		return (error_message("Malloc failed"));
	}
	return (0);
}

int	init_mutex_forks(t_simul *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->print_lock);
			pthread_mutex_destroy(&data->eat_lock);
			pthread_mutex_destroy(&data->dead_lock);
			pthread_mutex_destroy(&data->start_mutex);
			free(data->forks);
			free(data->philos);
			return (error_message("Mutex initialization failed"));
		}
		i++;
	}
	return (0);
}

int	init_mutex_locks(t_simul *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (error_message("Mutex initialization failed"));
	if (pthread_mutex_init(&data->eat_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		return (error_message("Mutex initialization failed"));
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->eat_lock);
		return (error_message("Mutex initialization failed"));
	}
	if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->eat_lock);
		pthread_mutex_destroy(&data->dead_lock);
		return (error_message("Mutex initialization failed"));
	}
	return (0);
}
