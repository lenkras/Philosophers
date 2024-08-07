/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-01 17:46:28 by epolkhov          #+#    #+#             */
/*   Updated: 2024-08-01 17:46:28 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	ft_isdigit(int arg)
{
	if (arg >= '0' && arg <= '9')
		return (1);
	else
		return (0);
}

static int	ft_isspace(int arg)
{
	if ((arg >= 9 && arg <= 13) || arg == 32)
		return (1);
	else
		return (0);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

size_t	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(t_philo *philo, size_t time)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < time)
	{
		if (check_if_dead(philo))
			return (1);
		usleep(100);
	}
	return (0);
}
