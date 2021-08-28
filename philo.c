/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:21:19 by mclam             #+#    #+#             */
/*   Updated: 2021/08/21 17:21:19 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_forks(int i, t_phil *phil)
{
	if (LEFT > RIGHT)
	{
		pthread_mutex_unlock(&phil->s[LEFT]->mutex_fork);
		pthread_mutex_unlock(&phil->s[RIGHT]->mutex_fork);
		print_msg(get_time(phil->time_start), phil, MSG_SLEEPING);
	}
	else
	{
		pthread_mutex_unlock(&phil->s[RIGHT]->mutex_fork);
		pthread_mutex_unlock(&phil->s[LEFT]->mutex_fork);
		print_msg(get_time(phil->time_start), phil, MSG_SLEEPING);
	}
}

void	take_forks(int i, t_phil *phil)
{
	if (LEFT < RIGHT)
	{
		pthread_mutex_lock(&phil->s[LEFT]->mutex_fork);
		print_msg(get_time(phil->time_start), phil, MSG_TAKEN_FORK);
		pthread_mutex_lock(&phil->s[RIGHT]->mutex_fork);
		print_msg(get_time(phil->time_start), phil, MSG_EATING);
	}
	else
	{
		pthread_mutex_lock(&phil->s[RIGHT]->mutex_fork);
		print_msg(get_time(phil->time_start), phil, MSG_TAKEN_FORK);
		pthread_mutex_lock(&phil->s[LEFT]->mutex_fork);
		print_msg(get_time(phil->time_start), phil, MSG_EATING);
	}
}

void	*philosopher(t_phil *phil)
{
	while (phil->eat_cntr < phil->v->number_of_times_each_philosopher_must_eat)
	{
		take_forks(phil->id, phil);
		eating(phil);
		put_forks(phil->id, phil);
		sleeping(phil);
		print_msg(get_time(phil->time_start), phil, MSG_THINKING);
	}
	return (NULL);
}
