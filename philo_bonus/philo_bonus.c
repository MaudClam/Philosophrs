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
		if (take_forks(v) == ERROR)
			break ;
		if (eating(v) == ERROR)
		{
			sem_post(v->sem_monitor);
			put_forks(v);
			break ;
		}
		put_forks(v);
		if (sleeping(v) == ERROR)
			break ;
		print_msg(getime(v->time_start), v, MSG_THINKING, TURQUOISE);
	}
	sem_wait(v->sem_forks);
	v->thread_compltd = TRUE;
	sem_post(v->sem_forks);
	return (NULL);
}

int	take_forks(t_var *v)
{
	time_t	time_start_bifurcate;

	time_start_bifurcate = getime(v->time_start);
	if (v->num_of_phils == 1)
	{
		print_msg(time_start_bifurcate, v, MSG_TAKEN_FORK, YELLOW);
		while (getime(v->time_start) - time_start_bifurcate <= v->time_to_die)
			usleep(TIME_DELAY);
		return (ERROR);
	}
	sem_wait(v->sem_forks);
	print_msg(getime(v->time_start), v, MSG_TAKEN_FORK, YELLOW);
	sem_wait(v->sem_forks);
	return (SUCCESS);
}

int	eating(t_var *v)
{
	sem_wait(v->sem_monitor);
	v->time_start_eat = getime(v->time_start);
	if (v->time_start_eat - v->time_last_ate < v->time_to_die)
	{
		v->time_last_ate = v->time_start_eat;
		sem_post(v->sem_monitor);
		print_msg(v->time_start_eat, v, MSG_EATING, GREEN);
	}
	else
		return (ERROR);
	while (getime(v->time_start) - v->time_start_eat < v->time_to_eat)
		usleep(TIME_DELAY);
	sem_wait(v->sem_monitor);
	if (++v->eat_counter == v->num_of_times_each_phil_must_eat)
		return (ERROR);
	else if (v->eat_counter == INT_MAX)
		v->eat_counter = 0;
	sem_post(v->sem_monitor);
	return (SUCCESS);
}

void	put_forks(t_var *v)
{
	sem_post(v->sem_forks);
	sem_post(v->sem_forks);
}

int	sleeping(t_var *v)
{
	time_t	time_start_sleep;

	time_start_sleep = getime(v->time_start);
	print_msg(time_start_sleep, v, MSG_SLEEPING, GRAY);
	while (getime(v->time_start) - time_start_sleep <= v->time_to_sleep)
		if (v->time_start_eat - v->time_last_ate < v->time_to_die)
			usleep(TIME_DELAY);
		else
			return (ERROR);
	return (SUCCESS);
}
