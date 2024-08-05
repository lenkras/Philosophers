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
	pthread_mutex_lock(&philo->main->dead_lock);
	if (philo->main->died == 1)
	{
		pthread_mutex_unlock(&philo->main->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->dead_lock);
	return (0);
}

// int	check_if_dead(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->main->dead_lock);
// 	int is_dead = philo->main->died;
// 	pthread_mutex_unlock(&philo->main->dead_lock);
// 	return is_dead;
// }

void	philo_think(t_philo *philo)
{
	if (check_if_dead(philo))
		return ;
	message(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	message(philo, "is sleeping");
	ft_usleep(philo, philo->main->period_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	printf("philo id: %d\n", philo->id);
	if (philo->main->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		message(philo, "has taken a fork");
		ft_usleep(philo, philo->main->period_to_die);
		//message(philo, "died");
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->main->dead_lock);
		*philo->philo_died = 1;
		pthread_mutex_unlock(&philo->main->dead_lock);
		return ;
	}
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
	// pthread_mutex_unlock(philo->left_fork);
    // pthread_mutex_unlock(philo->right_fork);

}


void	check_if_simul_start(t_philo *philo)
{
	pthread_mutex_lock(philo->start_mutex);
	while (*(philo->start_simulation) == 0)
	{
		pthread_mutex_unlock(philo->start_mutex);
		usleep (1000);
		pthread_mutex_lock(philo->start_mutex);
	}
	pthread_mutex_unlock(philo->start_mutex);
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
		ft_usleep(philo, philo->main->period_to_eat - 2);
	}
	while (!check_if_dead(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
