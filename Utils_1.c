/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:37:47 by aoukhart          #+#    #+#             */
/*   Updated: 2022/08/13 00:48:53 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	ret;
	int	i;
	int	sign;

	ret = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		ret = (ret * 10) + (nptr[i++] - '0');
	return (ret * sign);
}

long	c_time_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	sleep_ms(int t)
{
	usleep(1000 * t);
}

long	time_diff(t_ph *ph)
{
	return (c_time_ms() - ph->start);
}

void	print_state(t_ph *ph, char *state, char *color)
{
	if (ph->alive)
	{
		pthread_mutex_lock(ph->printing);
		printf("%s(%ld) %d %s\033[0m\n", color, time_diff(ph), ph->id, state);
		pthread_mutex_unlock(ph->printing);
	}
}
