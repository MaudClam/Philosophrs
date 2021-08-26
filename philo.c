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
	phil->s[i]->state = THINKING;
	test(LEFT, phil);
	test(RIGHT, phil);
	pthread_mutex_unlock(&phil->v->mutex_exclsn);
}

void	take_forks(int i, t_phil *phil)
{
	pthread_mutex_lock(&phil->v->mutex_exclsn);
	phil->s[i]->state = HUNGRY;
	test(i, phil);
	pthread_mutex_unlock(&phil->v->mutex_exclsn);
	pthread_mutex_lock(&phil->s[phil->id]->mutex_state);
}

void	*philosopher(t_phil *phil)
{
//	while (TRUE)
//	{
//		think();
//		take_forks(phil->id, phil);
//		eat();
//		put_forks(phil->id, phil);
		print_msg(phil, "Hi from philosopher");
//	}
	return (NULL);
}
