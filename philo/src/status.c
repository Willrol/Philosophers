/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:56:34 by aditer            #+#    #+#             */
/*   Updated: 2024/10/24 16:24:15 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_sleeping(t_philo *philo)
{
	if (get_dead(philo) || philo->eat_count_max == 0)
		return (false);
	secure_print(philo, "is sleeping", SLEEP);
	if (!ft_usleep(philo->time_to_sleep, philo))
		return (false);
	return (true);
}

int	get_eat_count(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(philo->eat_count_mutex);
	eat_count = philo->eat_count_max;
	pthread_mutex_unlock(philo->eat_count_mutex);
	return (eat_count);
}

void	put_forks(t_philo *philo)
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
	if (!ft_usleep(philo->time_to_eat, philo))
		return (put_forks(philo), false);
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

bool	take_forks(t_philo *philo)
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
	if (philo->nb_of_philo % 4 != 0)
	{
		if (philo->time_to_eat > philo->time_to_sleep)
			thinking_time = philo->time_to_eat - philo->time_to_sleep;
		if (philo->id % 2 != 0)
		{
			if (!ft_usleep((philo->time_to_eat / 2) + thinking_time, philo))
				return (false);
		}
		else
		{
			if (!ft_usleep(thinking_time, philo))
				return (false);
		}
	}
	if (!take_forks(philo))
		return (false);
	return (true);
}
