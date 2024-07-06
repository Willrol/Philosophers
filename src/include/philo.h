/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:31:54 by aditer            #+#    #+#             */
/*   Updated: 2024/07/06 18:13:07 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_struct.h"
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

// -----UTILS-----

int	ft_atoi(const char *nptr);
int	ft_ispositive_number(char *str);
size_t	get_time(void);

// -----THREADS-----

void	*routine(void *arg);
void	init_threads(t_data *data);
void	exit_prog(t_data *data);
#endif