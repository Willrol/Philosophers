/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:05:38 by aditer            #+#    #+#             */
/*   Updated: 2024/10/28 17:00:12 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
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

static void	init_philo(t_philo *philo, t_data *data, int i, time_t start_time)
{
	philo->id = i + 1;
	philo->nb_of_philo = data->nb_of_philo;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->last_eat = start_time;
	philo->start_time = start_time;
	philo->eat_count_max = data->eat_count_max;
	philo->finish_eating = false;
	philo->first_turn = true;
	philo->dead = false;
	philo->dead_mutex = &data->dead_mutex;
	philo->last_eat_mutex = &data->last_eat_mutex;
	philo->eat_count_mutex = &data->eat_count_mutex;
	philo->print_mutex = &data->print_mutex;
	philo->finish_eating_mutex = &data->finish_eating_mutex;
}

void	init_threads(t_data *data)
{
	long	start_time;
	int		i;

	i = 0;
	start_time = get_time();
	while (i < data->nb_of_philo)
	{
		init_philo(&data->philos[i], data, i, start_time);
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

void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->last_eat_mutex, NULL);
	pthread_mutex_init(&data->eat_count_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->finish_eating_mutex, NULL);
}

void	exit_prog(t_data *data)
{
	int	i;

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
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->last_eat_mutex);
	pthread_mutex_destroy(&data->eat_count_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->finish_eating_mutex);
}
