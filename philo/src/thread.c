/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:05:38 by aditer            #+#    #+#             */
/*   Updated: 2024/10/24 15:42:56 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_dead(t_philo *philo)
{
	bool	dead;

	pthread_mutex_lock(philo->dead_mutex);
	dead = philo->dead;
	pthread_mutex_unlock(philo->dead_mutex);
	return (dead);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	bool	dead;

	philo = (t_philo *)arg;
	dead = get_dead(philo);
	while (!dead)
	{
		if (!is_thinking(philo))
			break ;
		if (!is_eating(philo))
			break ;
		if (!is_sleeping(philo))
			break ;
		dead = get_dead(philo);
	}
	return (NULL);
}

void	init_threads(t_data *data)
{
	long	start_time;
	int		i;

	i = 0;
	start_time = get_time();
	while (i < data->nb_of_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_of_philo = data->nb_of_philo;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].last_eat = start_time;
		data->philos[i].start_time = start_time;
		data->philos[i].eat_count_max = data->eat_count_max;
		data->philos[i].dead = false;
		data->philos[i].dead_mutex = &data->dead_mutex;
		data->philos[i].last_eat_mutex = &data->last_eat_mutex;
		data->philos[i].eat_count_mutex = &data->eat_count_mutex;
		data->philos[i].print_mutex = &data->print_mutex;
		pthread_mutex_init(&data->philos[i].r_fork, NULL);
		if (i != 0)
			data->philos[i].l_fork = &data->philos[i - 1].r_fork;
		i++;
	}
	data->philos[0].l_fork = &data->philos[data->nb_of_philo - 1].r_fork;
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_create(&data->philos[i].philo_thread, NULL, routine,
			&data->philos[i]);
		i++;
	}
}

void	exit_prog(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(data->philos[i].l_fork);
		i++;
	}
}