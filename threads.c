/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 17:29:40 by mclam             #+#    #+#             */
/*   Updated: 2021/08/23 17:29:40 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	death_monitor(t_var *v, t_phil **phil)
{
	int		i;
	
	while (TRUE)
	{
		usleep(INTERVAL_OF_DEATH_MONITORING);
		i = 0;
		while (i < N)
		{
			pthread_mutex_lock(&phil[i]->mutex_t_eat);
			if (get_time(phil[0]->time_start) - phil[0]->time_last_ate > \
														phil[0]->v->time_to_die)
			{
				pthread_mutex_unlock(&phil[i]->mutex_t_eat);
//				pthread_mutex_lock(&phil[i]->v->mutex_death);
				v->number_of_times_each_philosopher_must_eat = 0;
//				pthread_mutex_unlock(&phil[i]->v->mutex_death);
				pthread_mutex_lock(&phil[i]->v->mutex_stdout);
				printf("%ld %d%s", get_time(phil[i]->time_start), \
													phil[i]->id + 1, MSG_DIED);
				pthread_mutex_unlock(&phil[i]->v->mutex_stdout);
				return (200);
			}
			pthread_mutex_unlock(&phil[i]->mutex_t_eat);
			i++;
		}
	}
	return (0);
}

int	detach_threads(t_var *v, t_phil **phil, int counter)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		if (pthread_detach(phil[i]->th))
		{
			errmsg_mutex("Faled to detach thread", errno, v);
			break ;
		}
		i++;
	}
	return (0);
}

int		init_mutex(void **a, int a_size, int *counter, pthread_mutex_t *mutex)
{
	if (*counter < a_size)
	{
		if (pthread_mutex_init(mutex, NULL))
		{
			destroy_mutexes(a, *counter);
			return (-1);
		}
		a[*counter] = mutex;
		(*counter)++;
	}
	else
	{
		destroy_mutexes(a, *counter);
		return (-1);
	}
	return (0);
}

int	init_mutexes(t_var *v, t_phil **phil)
{
	int i;
	
	i = 0;
	if (init_mutex(v->array_of_mutexes, NUMBER_OF_MUTEXES, \
									&v->counter_of_mutexes, &v->mutex_death))
		return (-1);
	if (init_mutex(v->array_of_mutexes, NUMBER_OF_MUTEXES, \
									&v->counter_of_mutexes, &v->mutex_stdout))
		return (-1);
	while (i < N)
	{
		if (init_mutex(v->array_of_mutexes, NUMBER_OF_MUTEXES, \
						&v->counter_of_mutexes, &phil[i]->s[i]->mutex_fork))
			return (-1);
		if (init_mutex(v->array_of_mutexes, NUMBER_OF_MUTEXES, \
								&v->counter_of_mutexes, &phil[i]->mutex_t_eat))
			return (-1);
		i++;
	}
	return (0);
}

int	start_threads(t_var *v, t_phil **phil)
{
	int		i;
	long	time_start;

	if (init_mutexes(v, phil))
	{
		errmsg("init_mutexess() error in start_threads()", -1);
		return (-1);
	}
	i = 0;
	time_start = get_time(0);
	while (i < N)
	{
		phil[i]->time_start = time_start;
		if (i == MAX_NUM_OF_THREADS || \
			pthread_create(&phil[i]->th, NULL, (void *)&philosopher, phil[i]))
		{
			errmsg_mutex("Faled to create thread", errno, v);
			break ;
		}
		i++;
	}
	detach_threads(v, phil, N);
	death_monitor(v, phil);
	destroy_mutexes(v->array_of_mutexes, v->counter_of_mutexes);
	return (0);
}
