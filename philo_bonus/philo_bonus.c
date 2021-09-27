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

void	philosopher(t_var *v)
{
	pthread_t	th;

	sem_wait(v->sem_stdout);
	v->time_start = getime(0);
	usleep(v->phil_id * TIME_DELAY);
	if (pthread_create(&th, NULL, (void *)&death_monitor, v) != SUCCESS)
		exit(free_mem(v, errmsg("Failed to create thread", errno)));
	while (TRUE)
	{
		if (take_forks(v) == ERROR)
			break ;
		if (eating(v) == ERROR)
			break ;
		put_forks(v);
		sleeping(v);
		print_msg(getime(v->time_start), v, MSG_THINKING, TURQUOISE);
	}
	free_mem(v, WITHOUT_SEM_CLOSE);
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
	{
		sem_post(v->sem_monitor);
		put_forks(v);
		return (ERROR);
	}
	while (getime(v->time_start) - v->time_start_eat < v->time_to_eat)
		usleep(TIME_DELAY);
	if (++v->eat_counter == v->num_of_times_each_phil_must_eat)
	{
		put_forks(v);
		free_mem(v, WITHOUT_SEM_CLOSE);
		exit(EXIT_SUCCESS);
	}
	else if (v->eat_counter == INT_MAX)
		v->eat_counter = 0;
	return (SUCCESS);
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
	while (getime(v->time_start) - time_start_sleep <= v->time_to_sleep)
		usleep(TIME_DELAY);
}
