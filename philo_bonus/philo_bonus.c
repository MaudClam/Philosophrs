/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:21:19 by mclam             #+#    #+#             */
/*   Updated: 2021/09/22 03:06:23 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

int	philosopher(t_var *v)
{
	open_semaphores(v);
	while (v->eat_counter < v->num_of_times_each_phil_must_eat)
	{
		if (take_forks(v) == ERROR)
		{
			print_msg(getime(v->time_start), v, MSG_DIED);
			exit(ERROR);
		}
		if (eating(v) == ERROR)
		{
			put_forks(v);
			print_msg(getime(v->time_start), v, MSG_DIED);
			exit(ERROR);
		}
		put_forks(v);
		if (sleeping(v) == ERROR)
		{
			print_msg(getime(v->time_start), v, MSG_DIED);
			exit(ERROR);
		}
		print_msg(getime(v->time_start), v, MSG_THINKING);
	}
	exit(SUCCESS);
}

int	take_forks(t_var *v)
{
	sem_wait(v->sem_forks);
	if (getime(v->time_start) - v->time_last_ate < v->time_to_die)
		print_msg(getime(v->time_start), v, MSG_TAKEN_FORK);
	else
	{
		sem_post(v->sem_forks);
		return (ERROR);
	}
	sem_wait(v->sem_forks);
	return (SUCCESS);
}

void	put_forks(t_var *v)
{
	sem_post(v->sem_forks);
	sem_post(v->sem_forks);
}

int	eating(t_var *v)
{
	time_t	time_start_eat;

	time_start_eat = getime(v->time_start);
	if (time_start_eat - v->time_last_ate < v->time_to_die)
	{
		print_msg(time_start_eat, v, MSG_EATING);
		v->time_last_ate = time_start_eat;
	}
	else
		return (ERROR);
	while (getime(v->time_start) - time_start_eat < v->time_to_eat)
	{
		if (getime(v->time_start) - v->time_last_ate < v->time_to_die)
			usleep(TIME_INTERVAL);
		else
			return (ERROR);
	}
	v->eat_counter++;
	return (SUCCESS);
}

int	sleeping(t_var *v)
{
	time_t	time_start_sleep;

	time_start_sleep = getime(v->time_start);
	print_msg(time_start_sleep, v, MSG_SLEEPING);
	while (getime(v->time_start) - time_start_sleep < v->time_to_sleep)
	{
		if (getime(v->time_start) - v->time_last_ate < v->time_to_die)
			usleep(TIME_INTERVAL);
		else
			return (ERROR);
	}
	return (TRUE);
}
