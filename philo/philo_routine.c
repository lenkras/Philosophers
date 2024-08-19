/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-03 13:13:29 by epolkhov          #+#    #+#             */
/*   Updated: 2024-08-03 13:13:29 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	check_if_dead(t_philo *philo)
{
	int	is_dead;

	is_dead = 0;
	pthread_mutex_lock(&philo->main->dead_lock);
	is_dead = philo->main->died;
	pthread_mutex_unlock(&philo->main->dead_lock);
	return (is_dead);
}

void	philo_think(t_philo *philo)
{
	if (check_if_dead(philo))
		return ;
	message(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	if (check_if_dead(philo))
		return ;
	message(philo, "is sleeping");
	ft_usleep(philo, philo->main->period_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	check_if_simul_start(philo);
	if (philo->main->num_of_philos == 1)
	{
		philo_eat(philo);
		return (NULL);
	}
	if (philo->id % 2 == 1)
	{
		philo_think(philo);
		usleep(1000);
	}
	while (!check_if_dead(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
