/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:15:56 by aoukhart          #+#    #+#             */
/*   Updated: 2022/08/13 21:06:25 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define RED  "\033[0;31m"
# define BLUE "\x1B[36m"
# define GRN	"\x1B[32m"
# define NRM	"\x1B[37m"
# define YLW "\033[0;33m"
# define EAT "is eating"
# define FRK "has taken a fork"
# define SLP "is sleeping"
# define TNK "is thinking"

typedef struct s_data
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_t_eat;

}	t_data;

typedef struct s_ph
{
	int				id;
	pthread_t		philo;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*printing;
	pthread_mutex_t	lock;
	pthread_mutex_t	dead;
	t_data			data;
	int				n_meals;
	int				alive;
	long			start;
	long			t_last_meal;
	int				eating;
}	t_ph;

int		ft_atoi(const char *nptr);
long	c_time_ms(void);
void	sleep_ms(int t);
long	time_diff(t_ph *ph);
void	print_state(t_ph *ph, char *state, char *color);
void	report_dead(t_ph *ph);
int		meals_count(t_ph *ph);
int		starvation(t_ph *ph);
void	*life(void *philo);
int		supervisors(t_ph *philo);
int		check_forbidden(char *s);

#endif