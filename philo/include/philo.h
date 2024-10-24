/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:31:54 by aditer            #+#    #+#             */
/*   Updated: 2024/10/24 14:40:24 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_struct.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define THINK "\033[0;34m"
# define FORK "\033[0;35m"
# define EAT "\033[0;32m"
# define SLEEP "\033[0;33m"
# define DEAD "\033[0;31m"
# define RESET "\033[0m"

// -----UTILS-----

long	get_time(void);
int		ft_atoi(const char *nptr);
int		ft_ispositive_number(char *str);
bool	ft_usleep(long time, t_philo *philo);

// -----THREADS-----

void	*routine(void *arg);
void	init_threads(t_data *data);
void	exit_prog(t_data *data);

// -----STATUS-----

bool	is_thinking(t_philo *philo);
bool	is_eating(t_philo *philo);
bool	is_sleeping(t_philo *philo);
bool	check_dead(t_data *data);

// -----GETTERS-----

bool	get_dead(t_philo *philo);
int		get_eat_count(t_philo *philo);

void	secure_print(t_philo *philo, char *str, char *color);

#endif