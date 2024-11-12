/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:26:01 by aditer            #+#    #+#             */
/*   Updated: 2024/10/29 11:42:04 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
