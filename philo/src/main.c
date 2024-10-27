/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:32:02 by aditer            #+#    #+#             */
/*   Updated: 2024/10/27 14:31:01 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (check_args(&data, argc, argv))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	data.philos = malloc(sizeof(t_philo) * data.nb_of_philo);
	pthread_mutex_init(&data.dead_mutex, NULL);
	pthread_mutex_init(&data.last_eat_mutex, NULL);
	pthread_mutex_init(&data.eat_count_mutex, NULL);
	pthread_mutex_init(&data.print_mutex, NULL);
	init_threads(&data);
	while (check_dead(&data))
		;
	exit_prog(&data);
	free(data.philos);
	return (0);
}
