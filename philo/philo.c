/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:21:19 by mclam             #+#    #+#             */
/*   Updated: 2021/09/01 02:22:44 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	sleeping(t_phil *phil)
{
	time_t	time_start_sleep;

	time_start_sleep = getime(phil->v->time_start);
	while (getime(phil->v->time_start) - time_start_sleep < \
														phil->v->time_to_sleep)
	{
		if (getime(phil->v->time_start) - phil->time_last_ate > \
														phil->v->time_to_die)
			return (FALSE);
		usleep(500);
	}
	return (TRUE);
}

int	eating(t_phil *phil)
{
	long	time_start_eat;

	pthread_mutex_lock(&phil->mutex_t_eat);
	time_start_eat = getime(phil->v->time_start);
	if (getime(phil->v->time_start) - time_start_eat > phil->v->time_to_die)
	{
		pthread_mutex_unlock(&phil->mutex_t_eat);
		return (FALSE);
	}
	phil->time_last_ate = time_start_eat;
	pthread_mutex_unlock(&phil->mutex_t_eat);
	print_msg(getime(phil->v->time_start), phil, MSG_EATING);
	while (getime(phil->v->time_start) - time_start_eat < phil->v->time_to_eat)
		usleep(TIME_MONITOR);
	pthread_mutex_lock(&phil->mutex_t_eat);
	if (phil->eat_counter++ == INT_MAX)
		phil->eat_counter = 0;
	pthread_mutex_unlock(&phil->mutex_t_eat);
	return (TRUE);
}

int	put_forks(int right, t_phil *phil)
{
	if (left(right, phil->v->pnu) > right)
	{
		pthread_mutex_unlock(&phil->f[left(right, phil->v->pnu)]->mutex_fork);
		pthread_mutex_unlock(&phil->f[right]->mutex_fork);
		print_msg(getime(phil->v->time_start), phil, MSG_SLEEPING);
	}
	else
	{
		pthread_mutex_unlock(&phil->f[right]->mutex_fork);
		pthread_mutex_unlock(&phil->f[left(right, phil->v->pnu)]->mutex_fork);
		print_msg(getime(phil->v->time_start), phil, MSG_SLEEPING);
	}
	return (TRUE);
}

int	take_forks(int right, t_phil *phil)
{
	if (left(right, phil->v->pnu) < right)
	{
		pthread_mutex_lock(&phil->f[left(right, phil->v->pnu)]->mutex_fork);
		print_msg(getime(phil->v->time_start), phil, MSG_TAKEN_FORK);
		pthread_mutex_lock(&phil->f[right]->mutex_fork);
	}
	else if (left(right, phil->v->pnu) > right)
	{
		pthread_mutex_lock(&phil->f[right]->mutex_fork);
		print_msg(getime(phil->v->time_start), phil, MSG_TAKEN_FORK);
		pthread_mutex_lock(&phil->f[left(right, phil->v->pnu)]->mutex_fork);
	}
	else
		return (FALSE);
	return (TRUE);
}

void	*philosopher(t_phil *phil)
{
	while (phil-> eat_counter < \
							phil->v->number_of_times_each_philosopher_must_eat)
	{
		if (take_forks(phil->i, phil) == FALSE)
			break ;
		if (eating(phil) == FALSE)
		{
			put_forks(phil->i, phil);
			break ;
		}
		put_forks(phil->i, phil);
		if (sleeping(phil) == FALSE)
			break ;
		print_msg(getime(phil->v->time_start), phil, MSG_THINKING);
	}
	pthread_mutex_lock(&phil->mutex_t_eat);
	phil->thread_compltd = TRUE;
	pthread_mutex_unlock(&phil->mutex_t_eat);
	return (NULL);
}
