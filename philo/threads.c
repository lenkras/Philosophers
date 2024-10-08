/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 16:16:11 by epolkhov          #+#    #+#             */
/*   Updated: 2024-08-07 16:16:11 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	join_threads(t_simul *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (error_message("Failed to join threads"));
		i++;
	}
	return (0);
}

static int	create_with_pthread(t_simul *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, \
				&data->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_detach(data->philos[i].thread);
			return (error_message("Failed to create thread"));
		}
		i++;
	}
	return (0);
}

int	create_threads(t_simul *data)
{
	pthread_t		monitor;

	if (create_with_pthread(data))
		return (1);
	data->start_time = current_time();
	if (pthread_create(&monitor, NULL, &simul_monitor, data) != 0)
	{
		join_threads(data);
		return (error_message("Failed to create monitor thread"));
	}
	pthread_mutex_lock(&data->start_mutex);
	data->start_simulation = 1;
	pthread_mutex_unlock(&data->start_mutex);
	if (pthread_join(monitor, NULL) != 0)
		return (error_message("Failed to join monitor thread"));
	if (join_threads(data))
		return (1);
	return (0);
}
