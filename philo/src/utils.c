/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:14:44 by aditer            #+#    #+#             */
/*   Updated: 2024/10/27 14:16:24 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_ispositive_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i])
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	if (res == 0)
		return (0);
	return (res);
}

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

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
