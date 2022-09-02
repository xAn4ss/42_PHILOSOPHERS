/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 04:09:12 by aoukhart          #+#    #+#             */
/*   Updated: 2022/08/13 21:06:15 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	starvation(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->data.n_philo)
	{
		pthread_mutex_lock(&ph[i].lock);
		if (ph[i].t_last_meal == 0)
			ph[i].t_last_meal = c_time_ms();
		if ((c_time_ms() - ph[i].t_last_meal) >= (ph[i].data.t_die + 20)
			&& ph[i].eating == 0)
		{
			pthread_mutex_lock(ph->printing);
			pthread_mutex_unlock(&ph[i].lock);
			printf("%s(%ld) %d is dead\033[0m\n", RED,
				time_diff(ph) - 20, ph->id);
			return (0);
		}
		pthread_mutex_unlock(&ph[i].lock);
		usleep(500);
		i++;
	}
	return (1);
}

int	meals_count(t_ph *ph)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (i < ph->data.n_philo)
	{
		pthread_mutex_lock(&ph[i].lock);
		if (ph->data.n_t_eat != 0 && ph[i].n_meals >= ph->data.n_t_eat)
			counter++;
		pthread_mutex_unlock(&ph[i].lock);
		i++;
	}
	if (counter == ph->data.n_philo)
	{
		pthread_mutex_lock(ph[0].printing);
		return (0);
	}
	return (1);
}

void	eat(t_ph *ph)
{
	print_state(ph, EAT, GRN);
	pthread_mutex_lock(&ph->lock);
	ph->eating = 1;
	ph->n_meals++;
	ph->t_last_meal = c_time_ms();
	pthread_mutex_unlock(&ph->lock);
	sleep_ms(ph->data.t_eat);
}

void	*life(void *philo)
{
	t_ph	*ph;

	ph = (t_ph *) philo;
	while (ph->alive)
	{
		pthread_mutex_lock(ph->right);
		print_state(ph, FRK, NRM);
		pthread_mutex_lock(ph->left);
		print_state(ph, FRK, NRM);
		eat(ph);
		pthread_mutex_unlock(ph->right);
		pthread_mutex_unlock(ph->left);
		pthread_mutex_lock(&ph->lock);
		ph->eating = 0;
		pthread_mutex_unlock(&ph->lock);
		print_state(ph, SLP, BLUE);
		sleep_ms(ph->data.t_sleep);
		print_state(ph, TNK, YLW);
	}
	return (NULL);
}

int	check_forbidden(char *s)
{
	int	i;
	int	counter;

	counter = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '+' || s[i] == '-')
		{
			if (s[i] == '-')
				return (0);
			i++;
		}
		if (s[i] < '0' || s[i] > '9')
			return (0);
		if (s[i] == '0')
			counter++;
	}
	if (counter == i)
		return (0);
	return (1);
}
