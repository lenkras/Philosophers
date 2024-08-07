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

static void	init_simulation(t_simul *data, char **argv, int argc)
{
	int	i;

	i = 0;
	if (init_arguments(data, argv, argc))
		return ;
	init_data(data);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	data->start_simulation = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philos(data);
}

int	main(int argc, char **argv)
{
	t_simul		data;

	if (argc < 5 || argc > 6)
		return (error_message("Invalid number of arguments"));
	if (check_args(argv))
		return (1);
	init_simulation(&data, argv, argc);
	if (data.meals_count == 0)
	{
		free_all(&data);
		return (error_message
			("Invalid number of times each philo should eat."));
	}
	if (create_threads(&data))
	{
		free_all(&data);
		return (1);
	}
	free_all(&data);
	return (0);
}
