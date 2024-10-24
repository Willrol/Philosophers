/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:14:44 by aditer            #+#    #+#             */
/*   Updated: 2024/10/24 15:14:46 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_ispositive_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i])
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	if (res == 0)
		return (0);
	return (res);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	ft_usleep(long time, t_philo *philo)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (get_dead(philo))
			return (false);
		usleep(100);
	}
	return (true);
}