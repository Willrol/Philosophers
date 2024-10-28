/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:32:02 by aditer            #+#    #+#             */
/*   Updated: 2024/10/28 11:02:05 by aditer           ###   ########.fr       */
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
	init_mutexes(&data);
	init_threads(&data);
	while (true)
		if (check_dead(&data) || check_finish_eating(&data))
			break ;
	exit_prog(&data);
	free(data.philos);
	return (0);
}
