/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:00:36 by aditer            #+#    #+#             */
/*   Updated: 2024/10/28 09:53:11 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	secure_print(t_philo *philo, char *str, char *color)
{
	if (get_dead(philo))
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf("%s%ld %d %s%s\n", color, (get_time() - philo->start_time),
		philo->id, str, RESET);
	pthread_mutex_unlock(philo->print_mutex);
}
