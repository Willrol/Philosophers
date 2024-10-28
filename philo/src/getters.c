/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:12:36 by aditer            #+#    #+#             */
/*   Updated: 2024/10/28 10:36:39 by aditer           ###   ########.fr       */
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

int	get_eat_count(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(philo->eat_count_mutex);
	eat_count = philo->eat_count_max;
	pthread_mutex_unlock(philo->eat_count_mutex);
	return (eat_count);
}

bool	get_finish_eating(t_philo *philo)
{
	bool	finish_eating;

	pthread_mutex_lock(philo->finish_eating_mutex);
	finish_eating = philo->finish_eating;
	pthread_mutex_unlock(philo->finish_eating_mutex);
	return (finish_eating);
}
bool	get_dead(t_philo *philo)
{
	bool	dead;

	pthread_mutex_lock(philo->dead_mutex);
	dead = philo->dead;
	pthread_mutex_unlock(philo->dead_mutex);
	return (dead);
}
