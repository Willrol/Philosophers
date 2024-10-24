/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:32:02 by aditer            #+#    #+#             */
/*   Updated: 2024/10/24 15:13:17 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_data *data, int argc, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_ispositive_number(argv[i]))
			return (1);
		data->nb_of_philo = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		data->eat_count_max = -1;
		if (argc == 6)
		{
			data->eat_count_max = ft_atoi(argv[5]);
			if (data->eat_count_max == 0)
				return (1);
		}
		if (data->nb_of_philo == 0 || data->time_to_die == 0
			|| data->time_to_eat == 0 || data->time_to_sleep == 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;

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