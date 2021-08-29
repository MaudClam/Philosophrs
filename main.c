/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:01:14 by mclam             #+#    #+#             */
/*   Updated: 2021/08/17 15:01:14 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	 init_variables(t_var *v, t_fork **f, t_phil **phil)
{
	int	i;

	i = 0;
	while (i < N)
	{
		phil[i]->id = i;
		phil[i]->f = f;
		phil[i]->v = v;
		i++;
	}
	v->array_of_mutexes = smart_calloc(v->array_of_mallocs, \
		NUMBER_OF_MALLOCS, &v->counter_of_mallocs, \
								sizeof(pthread_mutex_t) * NUMBER_OF_MUTEXES);
	if (!v->array_of_mutexes)
		return (errmsg("smart_calloc()[5] error in  init_variables()", -1));
	return (0);
}

t_phil	**init_phil(t_var *v)
{
	t_phil	*phil;
	t_phil	**phil_pt;
	int		i;

	phil = smart_calloc(v->array_of_mallocs, NUMBER_OF_MALLOCS, \
									&v->counter_of_mallocs, sizeof(t_phil) * N);
	if (!phil)
	{
		errmsg("smart_calloc()[3] error in init_phil()", -1);
		return (NULL);
	}
	phil_pt = smart_calloc(v->array_of_mallocs, NUMBER_OF_MALLOCS, \
						   &v->counter_of_mallocs, sizeof(t_phil *) * (N + 1));
	if (!phil_pt)
	{
		errmsg("smart_calloc()[4] error in init_phil()", -1);
		return (NULL);
	}
	i = N;
	phil_pt[i] = NULL;
	while (i--)
		phil_pt[i] = &phil[i];
	return (phil_pt);
}

t_fork	**init_forks(t_var *v)
{
	t_fork	*s;
	t_fork	**pt_s;
	int		i;

	s = smart_calloc(v->array_of_mallocs, NUMBER_OF_MALLOCS, \
					&v->counter_of_mallocs, sizeof(t_fork) * N);
	if (!s)
	{
		errmsg("smart_calloc()[1] error in init_forks()", -1);
		return (NULL);
	}
	pt_s = smart_calloc(v->array_of_mallocs, NUMBER_OF_MALLOCS, \
							&v->counter_of_mallocs, sizeof(t_fork *) * (N + 1));
	if (!pt_s)
	{
		errmsg("smart_calloc()[2] error in init_forks()", -1);
		return (NULL);
	}
	i = N;
	pt_s[i] = NULL;
	while (i--)
		pt_s[i] = &s[i];
	return (pt_s);
}

int	check_args(t_var *v)// The main() arguments will be added
{
	memset(v, 0, sizeof(t_var));
//	3 180 60 60
//	if (!FALSE)
//	return (errno);
	v->number_of_philosophers = 5;
	v->time_to_die = 400;
	v->time_to_eat = 200;
	v->time_to_sleep = 200;
	v->number_of_times_each_philosopher_must_eat = 7; //INT_MAX;
	v->array_of_mallocs = smart_calloc(NULL, NUMBER_OF_MALLOCS, \
					&v->counter_of_mallocs, sizeof(void *) * NUMBER_OF_MALLOCS);
	if (!v->array_of_mallocs)
		return (errmsg("smart_calloc()[0] error in main()", -1));
	return (0);
}

int main()
{
	t_var	v;
	t_fork	**f;
	t_phil	**phil;

	if (check_args(&v))// The main() arguments will be added
		return (errno);
	f = init_forks(&v);
	if (!f)
		return (errno);
	phil = init_phil(&v);
	if (!phil)
		return (errno);
	if ( init_variables(&v, f, phil))
		return (errno);
	if (start_threads(&v, phil))
	{
		free_mem(v.array_of_mallocs, v.counter_of_mallocs);
		return (errno);
	}
	usleep(1000000 + 100000 * v.number_of_philosophers);
	free_mem(v.array_of_mallocs, v.counter_of_mallocs);
	return (0);
}
