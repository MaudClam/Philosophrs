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
										&v->count_of_mutexes, &v->mutex_exclsn))
		return (-1);
	if (init_mutex(v->array_of_mutexes, NUMBER_OF_MUTEXES, \
										&v->count_of_mutexes, &v->mutex_stdout))
		return (-1);
	if (init_mutex(v->array_of_mutexes, NUMBER_OF_MUTEXES, \
										&v->count_of_mutexes, &v->mutex_stderr))
		return (-1);
	while (i < v->number_of_philosophers)
	{
		if (init_mutex(v->array_of_mutexes, NUMBER_OF_MUTEXES, \
							&v->count_of_mutexes, &phil[i]->s[i]->mutex_state))
			return (-1);
		i++;
	}
	return (0);
}

int	start_threads(t_var *v, t_phil **phil)
{
	int	i;

	i = 0;
	if (init_mutexes(v, phil))
	{
		errmsg("init_mutexess() error in start_threads()", errno);
		return (-1);
	}
	while (i < v->number_of_philosophers)
	{
		if (i == MAX_NUM_OF_THREADS || \
			pthread_create(&phil[i]->th, NULL, (void *)&philosopher, phil[i]))
		{
			errmsg_mutex("Faled to create thread", errno, v);
			break ;
		}
		i++;
	}
	detach_threads(v, phil, v->number_of_philosophers);
	destroy_mutexes(v->array_of_mutexes, v->count_of_mutexes);
	return (0);
}
