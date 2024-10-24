/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:13:09 by aditer            #+#    #+#             */
/*   Updated: 2024/10/24 14:05:33 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_eat(t_philo *philo)
{
	long	last_eat;

	pthread_mutex_lock(philo->last_eat_mutex);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(philo->last_eat_mutex);
	return (last_eat);
}

bool	check_time(t_philo *philo, long time_to_die)
{
	long	time;

	time = get_time() - get_last_eat(philo);
	if (time >= time_to_die)
	{
		if (get_eat_count(philo) != 0)
			secure_print(philo, "died", DEAD);
		pthread_mutex_lock(philo->dead_mutex);
		philo->dead = true;
		pthread_mutex_unlock(philo->dead_mutex);
		return (true);
	}
	return (false);
}

bool	check_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (check_time(&data->philos[i], data->time_to_die))
		{
			i = 0;
			while (i < data->nb_of_philo)
			{
				pthread_mutex_lock(data->philos[i].dead_mutex);
				data->philos[i].dead = true;
				pthread_mutex_unlock(data->philos[i].dead_mutex);
				i++;
			}
			return (false);
		}
		i++;
	}
	return (true);
}
