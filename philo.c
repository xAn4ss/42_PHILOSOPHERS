/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:16:46 by aoukhart          #+#    #+#             */
/*   Updated: 2022/08/13 21:06:32 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!check_forbidden(av[i]))
			return (0);
	}
	return (1);
}

void	init_param(t_ph *philo, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].data.n_philo = ft_atoi(av[1]);
		philo[i].data.t_die = ft_atoi(av[2]);
		philo[i].data.t_eat = ft_atoi(av[3]);
		philo[i].data.t_sleep = ft_atoi(av[4]);
		philo[i].id = i + 1;
		philo[i].n_meals = 0;
		philo[i].start = c_time_ms();
		philo[i].alive = 1;
		philo[i].t_last_meal = 0;
		philo[i].eating = 0;
		if (ac == 6)
			philo[i].data.n_t_eat = ft_atoi(av[5]);
		else
			philo[i].data.n_t_eat = 0;
		i++;
	}
}

void	init_mutexes(t_ph *philo, pthread_mutex_t *fork)
{
	int				i;
	pthread_mutex_t	*print;

	i = 0;
	print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print, NULL);
	while (i < philo->data.n_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		pthread_mutex_init(&philo[i].dead, NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		philo[i].printing = print;
		i++;
	}
	i = 0;
	while (i < philo->data.n_philo)
	{
		philo[i].right = &fork[i];
		philo[i].left = &fork[(i + 1) % philo->data.n_philo];
		i++;
	}
}

void	init_philosophers(t_ph *philo)
{
	int	i;

	i = 0;
	while (i < philo->data.n_philo)
	{
		if (pthread_create(&philo[i].philo, NULL, &life, &philo[i]))
		{
			write(2, "thread creation failed\n", 24);
			return ;
		}
		if (pthread_detach(philo[i].philo))
		{
			write(2, "thread creation failed\n", 24);
			return ;
		}		
		usleep(100);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_ph			*philo;
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		if (check_args(ac, av) == 0)
		{
			write(2, "Error.\n", 8);
			return (0);
		}
		fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
		philo = malloc(sizeof(t_ph) * ft_atoi(av[1]));
		init_param(philo, ac, av);
		init_mutexes(philo, fork);
		init_philosophers(philo);
		while (((starvation(philo)) & (meals_count(philo))))
			;
		free(philo);
		free(fork);
	}
	else
		write(2, "Error.\nCheck Arguments !!", 25);
}
