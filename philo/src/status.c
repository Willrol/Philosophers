/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:56:34 by aditer            #+#    #+#             */
/*   Updated: 2024/10/27 14:18:28 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_sleeping(t_philo *philo)
{
	if (get_dead(philo) || philo->eat_count_max == 0)
		return (false);
	secure_print(philo, "is sleeping", SLEEP);
	usleep(philo->time_to_sleep * 1000);
	return (true);
}

static void	put_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

bool	is_eating(t_philo *philo)
{
	if (get_dead(philo) || philo->eat_count_max == 0)
	{
		put_forks(philo);
		return (false);
	}
	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->last_eat_mutex);
	secure_print(philo, "is eating", EAT);
	usleep(philo->time_to_eat * 1000);
	if (get_eat_count(philo) > 0)
	{
		pthread_mutex_lock(philo->eat_count_mutex);
		philo->eat_count_max--;
		if (philo->eat_count_max == 0)
		{
			pthread_mutex_unlock(philo->eat_count_mutex);
			put_forks(philo);
			return (false);
		}
		pthread_mutex_unlock(philo->eat_count_mutex);
	}
	put_forks(philo);
	return (true);
}

static bool	take_forks(t_philo *philo)
{
	if (get_dead(philo) || philo->eat_count_max == 0)
		return (false);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		secure_print(philo, "has taken a fork", FORK);
		if (get_dead(philo) || philo->eat_count_max == 0)
			return (pthread_mutex_unlock(philo->l_fork), false);
		pthread_mutex_lock(&philo->r_fork);
		secure_print(philo, "has taken a fork", FORK);
	}
	else if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->r_fork);
		secure_print(philo, "has taken a fork", FORK);
		if (philo->nb_of_philo == 1 || get_dead(philo)
			|| philo->eat_count_max == 0)
			return (pthread_mutex_unlock(&philo->r_fork), false);
		pthread_mutex_lock(philo->l_fork);
		secure_print(philo, "has taken a fork", FORK);
	}
	return (true);
}

bool	is_thinking(t_philo *philo)
{
	long	thinking_time;

	thinking_time = 0;
	if (get_dead(philo) || philo->eat_count_max == 0)
		return (false);
	secure_print(philo, "is thinking", THINK);
	if (philo->nb_of_philo % 2 != 0
		&& philo->time_to_eat > philo->time_to_sleep)
		thinking_time = philo->time_to_eat - philo->time_to_sleep;
	if (philo->id % 2 != 0)
		usleep(5000 + thinking_time);
	else
	{
		if (philo->first_turn)
		{
			philo->first_turn = false;
			usleep(philo->time_to_eat * 500);
		}
	}
	if (!take_forks(philo))
		return (false);
	return (true);
}
