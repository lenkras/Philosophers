/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 17:04:04 by epolkhov          #+#    #+#             */
/*   Updated: 2024-08-07 17:04:04 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	one_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	message(philo, "has taken a fork");
	ft_usleep(philo, philo->main->period_to_die);
	message(philo, "died");
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->main->dead_lock);
	*philo->philo_died = 1;
	pthread_mutex_unlock(&philo->main->dead_lock);
	return ;
}

static void	start_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
	}
	message(philo, "has taken a fork");
	message(philo, "is eating");
}

void	philo_eat(t_philo *philo)
{
	if (philo->main->num_of_philos == 1)
	{
		one_philo_eat(philo);
		return ;
	}
	start_eating(philo);
	pthread_mutex_lock(&philo->main->eat_lock);
	philo->last_meal = current_time();
	philo->num_of_meal++;
	pthread_mutex_unlock(&philo->main->eat_lock);
	ft_usleep(philo, philo->main->period_to_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
