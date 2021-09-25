/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:21:19 by mclam             #+#    #+#             */
/*   Updated: 2021/09/25 07:00:53 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	philosopher(t_var *v)
{
	while (TRUE)
	{
		take_forks(v);
		eating(v);
		put_forks(v);
		sleeping(v);
		print_msg(getime(v->time_start), v, MSG_THINKING, TURQUOISE);
	}
}

void	take_forks(t_var *v)
{
	time_t	time_start_bifurcate;
	
	time_start_bifurcate = getime(v->time_start);
	if (v->num_of_phils > 1)
	{
		sem_wait(v->sem_forks);
		if (getime(v->time_start) - v->time_last_ate < v->time_to_die)
			print_msg(getime(v->time_start), v, MSG_TAKEN_FORK, YELLOW);
		else
			print_msg_died_and_exit(getime(v->time_start), v, ERROR);
		sem_wait(v->sem_forks);
	}
	else
	{
		print_msg(time_start_bifurcate, v, MSG_TAKEN_FORK, YELLOW);
		while (getime(v->time_start) - time_start_bifurcate < v->time_to_die)
			usleep(TIME_INTERVAL);
		print_msg_died_and_exit(getime(v->time_start), v, ERROR);
	}
}

void	eating(t_var *v)
{
	time_t	time_start_eat;

	time_start_eat = getime(v->time_start);
	if (time_start_eat - v->time_last_ate < v->time_to_die)
	{
		print_msg(time_start_eat, v, MSG_EATING, GREEN);
		v->time_last_ate = time_start_eat;
	}
	else
		print_msg_died_and_exit(getime(v->time_start), v, ERROR);
	while (getime(v->time_start) - time_start_eat < v->time_to_eat)
	{
		if (getime(v->time_start) - v->time_last_ate < v->time_to_die)
			usleep(TIME_INTERVAL);
		else
			print_msg_died_and_exit(getime(v->time_start), v, ERROR);
	}
	if (++v->eat_counter == v->num_of_times_each_phil_must_eat)
	{
		put_forks(v);
		exit(free_mem(v, SUCCESS));
	}
	else if (v->eat_counter == INT_MAX)
		v->eat_counter = 0;
}

void	put_forks(t_var *v)
{
	sem_post(v->sem_forks);
	sem_post(v->sem_forks);
}

void	sleeping(t_var *v)
{
	time_t	time_start_sleep;

	time_start_sleep = getime(v->time_start);
	print_msg(time_start_sleep, v, MSG_SLEEPING, GRAY);
	while (getime(v->time_start) - time_start_sleep < v->time_to_sleep)
	{
		if (getime(v->time_start) - v->time_last_ate < v->time_to_die)
			usleep(TIME_INTERVAL);
		else
			print_msg_died_and_exit(getime(v->time_start), v, ERROR);
	}
}
