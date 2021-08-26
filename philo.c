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

void	test(int i, t_phil *phil)
{
	if (phil->s[i]->state == HUNGRY && \
		phil->s[LEFT]->state != EATING && phil->s[RIGHT]->state != EATING)
	{
		phil->s[i]->state = EATING;
		pthread_mutex_unlock(&phil->s[i]->mutex_state);
	}
}

void	put_forks(int i, t_phil *phil)
{
	pthread_mutex_lock(&phil->v->mutex_exclsn);
	phil->s[i]->state = SLEEPING;
	test(LEFT, phil);
	test(RIGHT, phil);
	pthread_mutex_unlock(&phil->v->mutex_exclsn);
}

void	take_forks(int i, t_phil *phil)
{
	pthread_mutex_lock(&phil->v->mutex_exclsn);
	phil->s[i]->state = HUNGRY;
	print_msg(get_time(phil->time_start), phil, MSG_TAKEN_FORK);
	test(i, phil);
	pthread_mutex_unlock(&phil->v->mutex_exclsn);
	pthread_mutex_lock(&phil->s[i]->mutex_state);
}

void	*philosopher(t_phil *phil)
{
	while (phil->eat_cntr < phil->v->number_of_times_each_philosopher_must_eat)
	{
		take_forks(phil->id, phil);
		print_msg(get_time(phil->time_start), phil, MSG_EATING);
		eating(phil);
		put_forks(phil->id, phil);
		print_msg(get_time(phil->time_start), phil, MSG_SLEEPING);
		usleep(phil->v->time_to_sleep * 1000);
		pthread_mutex_lock(&phil->s[phil->id]->mutex_state);
		phil->s[phil->id]->state = THINKING;
		print_msg(get_time(phil->time_start), phil, MSG_THINKING);
		pthread_mutex_unlock(&phil->s[phil->id]->mutex_state);
	}
	return (NULL);
}
