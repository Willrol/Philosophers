/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:31:59 by aditer            #+#    #+#             */
/*   Updated: 2024/10/24 18:03:09 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*last_eat_mutex;
	pthread_mutex_t	*eat_count_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_t		philo_thread;
	long			start_time;
	long			time_to_eat;
	long			time_to_sleep;
	long			last_eat;
	int				id;
	int				nb_of_philo;
	int				eat_count_max;
	bool			dead;
	bool			first_turn;

}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	eat_count_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_of_philo;
	int				eat_count_max;

}					t_data;

#endif