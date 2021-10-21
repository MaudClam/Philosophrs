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

void	*philosopher(t_phil *phil)
{
	while (phil->eat_counter < phil->v->num_of_times_each_phil_must_eat)
	{
		if (take_forks(phil) == ERROR)
			break ;
		if (eating(phil) == ERROR)
		{
			put_forks(phil);
			break ;
		}
		put_forks(phil);
		sleeping(phil);
		print_msg(getime(phil->v->time_start_game), phil, MSG_THINKING);
	}
	pthread_mutex_lock(&phil->mutex_t_eat);
	phil->thread_compltd = TRUE;
	pthread_mutex_unlock(&phil->mutex_t_eat);
	return (NULL);
}

int	take_forks(t_phil *phil)
{
	time_t	t_start_tforks;

	if (phil->v->phnu == 1)
	{
		t_start_tforks = getime(phil->v->time_start_game);
		print_msg(t_start_tforks, phil, MSG_TAKEN_FORK);
		phil_timer(phil->v->time_start_game, t_start_tforks, \
														phil->v->time_to_die);
		return (ERROR);
	}
	if (phil->first < phil->seccond)
	{
		pthread_mutex_lock(&phil->f[phil->first]->mutex_fork);
		print_msg(getime(phil->v->time_start_game), phil, MSG_TAKEN_FORK);
		pthread_mutex_lock(&phil->f[phil->seccond]->mutex_fork);
	}
	else if (phil->first > phil->seccond)
	{
		pthread_mutex_lock(&phil->f[phil->seccond]->mutex_fork);
		print_msg(getime(phil->v->time_start_game), phil, MSG_TAKEN_FORK);
		pthread_mutex_lock(&phil->f[phil->first]->mutex_fork);
	}
	return (SUCCESS);
}

void	put_forks(t_phil *phil)
{
	if (phil->first > phil->seccond)
	{
		pthread_mutex_unlock(&phil->f[phil->first]->mutex_fork);
		pthread_mutex_unlock(&phil->f[phil->seccond]->mutex_fork);
	}
	else
	{
		pthread_mutex_unlock(&phil->f[phil->seccond]->mutex_fork);
		pthread_mutex_unlock(&phil->f[phil->first]->mutex_fork);
	}
}

int	eating(t_phil *phil)
{
	time_t	t_start_eat;

	pthread_mutex_lock(&phil->mutex_t_eat);
	t_start_eat = getime(phil->v->time_start_game);
	if ((t_start_eat - phil->time_last_ate) / FIND_TIMEDEATH_PRECSN <= \
								phil->v->time_to_die / FIND_TIMEDEATH_PRECSN)
	{
		phil->time_last_ate = t_start_eat;
		if (++phil->eat_counter == INT_MAX)
			phil->eat_counter = 0;
		pthread_mutex_unlock(&phil->mutex_t_eat);
		print_msg(t_start_eat, phil, MSG_EATING);
	}
	else
	{
		pthread_mutex_unlock(&phil->mutex_t_eat);
		return (ERROR);
	}
	phil_timer(phil->v->time_start_game, t_start_eat, phil->v->time_to_eat);
	return (SUCCESS);
}

void	sleeping(t_phil *phil)
{
	time_t	t_start_sleep;

	t_start_sleep = getime(phil->v->time_start_game);
	print_msg(t_start_sleep, phil, MSG_SLEEPING);
	phil_timer(phil->v->time_start_game, t_start_sleep, phil->v->time_to_sleep);
}
