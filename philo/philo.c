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

int	main(int argc, char **argv)
{
	t_simul		data;

	if (argc < 5 || argc > 6)
		return (error_message("Invalid number of arguments"));
	if (check_args(argv))
		return (1);
	if (init_simulation(&data, argv, argc))
		return (1);
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
