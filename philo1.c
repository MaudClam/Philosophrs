/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 20:32:03 by mclam             #+#    #+#             */
/*   Updated: 2021/08/25 20:32:03 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_philosopher_dead(t_phil *phil)
{
	pthread_mutex_lock(&phil->mutex_t_eat);
	if (get_time(phil->time_start) - phil->time_last_ate > \
														phil->v->time_to_die)
	{
		pthread_mutex_unlock(&phil->mutex_t_eat);
		return (TRUE);
	}
	pthread_mutex_unlock(&phil->mutex_t_eat);
	return (FALSE);
}

void	print_msg(long time, t_phil *phil, char *msg)
{
/*	char	death;
	
	death = FALSE;
	pthread_mutex_lock(&phil->v->mutex_death);
	if (phil->v->number_of_times_each_philosopher_must_eat == 0)
		death = TRUE;
	pthread_mutex_unlock(&phil->v->mutex_death);
	if (death == FALSE)
	{*/
		pthread_mutex_lock(&phil->v->mutex_stdout);
		printf("%ld %d%s", time, phil->id + 1, msg);
		pthread_mutex_unlock(&phil->v->mutex_stdout);
//	}
}

long	get_time(long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000 - start);
}

/*static void    ft_swap(long *a, long *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
*/
void	eating(t_phil *phil)
{
	long	time_start_eat;
	
	time_start_eat = get_time(phil->time_start);
	pthread_mutex_lock(&phil->mutex_t_eat);
	phil->time_last_ate = get_time(phil->time_start);
	pthread_mutex_unlock(&phil->mutex_t_eat);
	while (get_time(phil->time_start) - time_start_eat < phil->v->time_to_eat)
	{
		usleep(500);
/*		phil->meal = LONG_MAX;
		ft_swap(&phil->meal, &phil->belly);
		ft_swap(&phil->belly, &phil->feces);
		phil->feces = 0;
 */
	}
	pthread_mutex_lock(&phil->mutex_t_eat);
	phil->time_last_ate = get_time(phil->time_start);
	pthread_mutex_unlock(&phil->mutex_t_eat);
	if (phil->eat_cntr++ == INT_MAX)
		phil->eat_cntr = 0;
}

void	sleeping(t_phil *phil)
{
/*	long	time_start_slp;

	time_start_slp = get_time(phil->time_start);
	while (get_time(phil->time_start) - time_start_slp < phil->v->time_to_sleep)
		usleep(500);*/
	usleep(phil->v->time_to_sleep);
}
