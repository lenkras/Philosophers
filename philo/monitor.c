/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 16:34:52 by epolkhov          #+#    #+#             */
/*   Updated: 2024-08-07 16:34:52 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	philo_dead(t_simul *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->eat_lock);
		if (current_time() - data->philos[i].last_meal > data->period_to_die)
		{
			pthread_mutex_unlock(&data->eat_lock);
			message(&data->philos[i], "died");
			pthread_mutex_lock(&data->dead_lock);
			data->died = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->eat_lock);
		i++;
	}
	return (0);
}

int	task_complete(t_simul *data)
{
	int	i;
	int	ready;

	i = 0;
	ready = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->eat_lock);
		if (data->philos[i].num_of_meal >= data->meals_count)
			ready++;
		pthread_mutex_unlock(&data->eat_lock);
		i++;
	}
	if (ready == data->num_of_philos)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->died = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

void	check_if_simul_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->start_mutex);
	while (philo->main->start_simulation == 0)
	{
		pthread_mutex_unlock(&philo->main->start_mutex);
		usleep (1000);
		pthread_mutex_lock(&philo->main->start_mutex);
	}
	pthread_mutex_unlock(&philo->main->start_mutex);
}

void	*simul_monitor(void *arg)
{
	t_simul	*data;

	data = (t_simul *)arg;
	while (1)
	{
		if (philo_dead(data) == 1 || task_complete(data) == 1)
			break ;
		usleep (1000);
	}
	return (NULL);
}

void	free_all(t_simul *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->num_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->start_mutex);
}
