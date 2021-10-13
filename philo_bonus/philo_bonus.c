/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:21:19 by mclam             #+#    #+#             */
/*   Updated: 2021/09/26 04:02:19 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	*philosopher(t_var *v)
{
	while (v->eat_counter < v->num_of_times_each_phil_must_eat)
	{
		if (take_forks(v) != SUCCESS)
			break ;
		if (eating(v) != SUCCESS)
		{
			put_forks(v);
			break ;
		}
		put_forks(v);
		if (sleeping(v) != SUCCESS)
			break ;
		print_msg(getime(v->time_start), v, MSG_THINKING, TURQUOISE);
	}
	sem_wait(v->sem_monitor);
	v->thread_compltd = TRUE;
	sem_post(v->sem_monitor);
	return (NULL);
}

int	take_forks(t_var *v)
{
	time_t	time_start_tforks;

	time_start_tforks = getime(v->time_start);
	if (v->phnu == 1)
	{
		phil_timer(v->time_start, time_start_tforks, v->time_to_die);
		return (ERROR);
	}
	sem_wait(v->sem_fifo);
	sem_wait(v->sem_garcon_no2);
	sem_wait(v->sem_forks);
	print_msg(getime(v->time_start), v, MSG_TAKEN_FORK, YELLOW);
	sem_wait(v->sem_forks);
	return (SUCCESS);
}

int	eating(t_var *v)
{
	time_t	time_start_eat;

	sem_wait(v->sem_monitor);
	time_start_eat = getime(v->time_start);
	if ((time_start_eat - v->time_last_ate) / FIND_TIMEDEATH_PRECSN <= \
										v->time_to_die / FIND_TIMEDEATH_PRECSN)
	{
		v->time_last_ate = time_start_eat;
		if (++v->eat_counter == INT_MAX)
			v->eat_counter = 0;
		sem_post(v->sem_monitor);
		print_msg(time_start_eat, v, MSG_EATING, GREEN);
	}
	else
	{
		sem_post(v->sem_monitor);
		return (ERROR);
	}
	phil_timer(v->time_start, time_start_eat, v->time_to_eat);
	return (SUCCESS);
}

void	put_forks(t_var *v)
{
	sem_post(v->sem_forks);
	sem_post(v->sem_forks);
	sem_post(v->sem_garcon_no2);
	sem_post(v->sem_fifo);
}

int	sleeping(t_var *v)
{
	time_t	time_start_sleep;

	time_start_sleep = getime(v->time_start);
	print_msg(time_start_sleep, v, MSG_SLEEPING, GRAY);
	phil_timer(v->time_start, time_start_sleep, v->time_to_sleep);
	return (SUCCESS);
}
