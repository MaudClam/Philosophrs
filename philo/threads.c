/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 17:29:40 by mclam             #+#    #+#             */
/*   Updated: 2021/10/09 05:58:06 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	death_monitor(t_var *v, t_phil **phil)
{
	int		i;

	while (v->pnu)
	{
		usleep(TIME_MONITOR);
		i = 0;
		while (i < v->pnu)
		{
			pthread_mutex_lock(&phil[i]->mutex_t_eat);
			if (getime(v->time_start) - phil[i]->time_last_ate > \
														phil[i]->v->time_to_die)
			{
				if (phil[i]->eat_counter != \
				phil[i]->v->number_of_times_each_philosopher_must_eat)
					it_is_death(getime(v->time_start), phil[i]);
				pthread_mutex_unlock(&phil[i]->mutex_t_eat);
				game_over(v, phil);
				return ;
			}
			pthread_mutex_unlock(&phil[i]->mutex_t_eat);
			i++;
		}
	}
}

void	detach_threads(t_var *v, t_phil **phil, int counter)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		if (pthread_detach(phil[i]->th))
		{
			errmsg_mutex("Faled to detach thread", ERROR, v);
			return ;
		}
		i++;
	}
}

int	init_mutex(void **a, int a_size, int *counter, pthread_mutex_t *mutex)
{
	if (*counter < a_size)
	{
		if (pthread_mutex_init(mutex, NULL))
		{
			destroy_mutexes(a, *counter);
			return (ERROR);
		}
		a[*counter] = mutex;
		(*counter)++;
	}
	else
	{
		destroy_mutexes(a, *counter);
		return (ERROR);
	}
	return (SUCCESS);
}

int	init_mutexes(t_var *v, t_phil **phil)
{
	int	i;

	i = 0;
	if (init_mutex(v->array_of_mutexes, (v->pnu * 2 + 1), \
									&v->counter_of_mutexes, &v->mutex_stdout))
		return (errmsg("init_mutexes()1 error in init_mutexess()", ERROR));
	while (i < v->pnu)
	{
		if (init_mutex(v->array_of_mutexes, (v->pnu * 2 + 1), \
						&v->counter_of_mutexes, &phil[i]->f[i]->mutex_fork))
			return (errmsg("init_mutexes()2 error in init_mutexess()", ERROR));
		if (init_mutex(v->array_of_mutexes, (v->pnu * 2 + 1), \
								&v->counter_of_mutexes, &phil[i]->mutex_t_eat))
			return (errmsg("init_mutexes()3 error in init_mutexess()", ERROR));
		i++;
	}
	return (SUCCESS);
}

int	start_threads(t_var *v, t_phil **phil)
{
	int		i;

	if (init_mutexes(v, phil))
		return (ERROR);
	i = 0;
	v->time_start = getime(0);
	while (i < v->pnu)
	{
		if (pthread_create(&phil[i]->th, NULL, (void *)&philosopher, phil[i]))
		{
			errmsg_mutex("Faled to create thread", ERROR, v);
			destroy_mutexes(v->array_of_mutexes, v->counter_of_mutexes);
			return (ERROR);
		}
		usleep(TIME_DELAY);
		i++;
	}
	detach_threads(v, phil, v->pnu);
	death_monitor(v, phil);
	destroy_mutexes(v->array_of_mutexes, v->counter_of_mutexes);
	return (SUCCESS);
}
