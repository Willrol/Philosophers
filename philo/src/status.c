/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:56:34 by aditer            #+#    #+#             */
/*   Updated: 2024/10/29 12:40:57 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_sleeping(t_philo *philo)
{
	if (get_dead(philo) || philo->eat_count_max == 0)
		return (false);
	secure_print(philo, "is sleeping", SLEEP);
	ft_usleep(philo->time_to_sleep, philo);
	return (true);
}

bool	is_eating(t_philo *philo)
{
	if (get_dead(philo) || philo->eat_count_max == 0)
		return (put_forks(philo), false);
	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->last_eat_mutex);
	secure_print(philo, "is eating", EAT);
	ft_usleep(philo->time_to_eat, philo);
	if (get_eat_count(philo) > 0)
	{
		pthread_mutex_lock(philo->eat_count_mutex);
		philo->eat_count_max--;
		if (philo->eat_count_max == 0)
		{
			pthread_mutex_unlock(philo->eat_count_mutex);
			pthread_mutex_lock(philo->finish_eating_mutex);
			philo->finish_eating = true;
			pthread_mutex_unlock(philo->finish_eating_mutex);
			put_forks(philo);
			return (false);
		}
		pthread_mutex_unlock(philo->eat_count_mutex);
	}
	put_forks(philo);
	return (true);
}

bool	is_thinking(t_philo *philo)
{
	long	thinking_time;

	thinking_time = 0;
	if (get_dead(philo) || philo->eat_count_max == 0)
		return (false);
	if (philo->nb_of_philo % 2 != 0
		&& philo->time_to_eat > philo->time_to_sleep)
		thinking_time = philo->time_to_eat - philo->time_to_sleep;
	if (philo->id % 2 != 0)
	{
		secure_print(philo, "is thinking", THINK);
		ft_usleep(5 + thinking_time, philo);
	}
	else
	{
		secure_print(philo, "is thinking", THINK);
		if (philo->first_turn)
		{
			philo->first_turn = false;
			ft_usleep((philo->time_to_eat), philo);
		}
	}
	if (!take_forks(philo))
		return (false);
	return (true);
}
