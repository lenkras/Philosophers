/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-01 17:50:24 by epolkhov          #+#    #+#             */
/*   Updated: 2024-08-01 17:50:24 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	error_message(char *msg)
{
	printf("%s", msg);
	return (1);
}

int	check_if_digit(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (check_if_digit(argv[i]) || ft_atol(argv[i]) < 1)
		{
			return (error_message("Invalid input: \
			it must be a digit and positive number other than 0"));
		}
		i++;
	}
	return (0);
}

void	message(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&philo->main->print_lock);
	time = current_time() - philo->main->start_time;
	pthread_mutex_lock(&philo->main->dead_lock);
	if (!philo->main->died)
		printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->main->dead_lock);
	pthread_mutex_unlock(&philo->main->print_lock);
}
