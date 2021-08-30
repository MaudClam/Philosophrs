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

int	init_variables(t_var *v, t_fork **f, t_phil **phil)
{
	int	i;

	i = 0;
	while (i < N)
	{
		phil[i]->i = i;
		phil[i]->id = i + 1;
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

int	check_args(t_var *v, int argc, char **argv)
{
	if (argc < 2 || argc > 6)
		return (printf("%s", MSG_BAD_ARGUMENTS));
	v->number_of_philosophers = ft_atoi(argv[1]);
	if (v->number_of_philosophers < 1 || v->number_of_philosophers > 200)
		return (printf("%s", MSG_BAD_ARGUMENTS));
	v->time_to_die = ft_atoi(argv[2]);
	if (v->time_to_die < 60 || v->time_to_die > INT_MAX)
		return (printf("%s", MSG_BAD_ARGUMENTS));
	v->time_to_eat = ft_atoi(argv[3]);
	if (v->time_to_eat < 60 || v->time_to_die > INT_MAX)
		return (printf("%s", MSG_BAD_ARGUMENTS));
	v->time_to_sleep = ft_atoi(argv[4]);
	if (v->time_to_sleep < 60 || v->time_to_die > INT_MAX)
		return (printf("%s", MSG_BAD_ARGUMENTS));
	v->number_of_times_each_philosopher_must_eat = INT_MAX;
	if (argc == 6)
		v->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (v->number_of_times_each_philosopher_must_eat < 1 || \
						v->number_of_times_each_philosopher_must_eat > INT_MAX)
		return (printf("%s", MSG_BAD_ARGUMENTS));
	v->array_of_mallocs = smart_calloc(NULL, NUMBER_OF_MALLOCS, \
					&v->counter_of_mallocs, sizeof(void *) * NUMBER_OF_MALLOCS);
	if (!v->array_of_mallocs)
		return (errmsg("smart_calloc()[0] error in check_args()", -1));
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	v;
	t_fork	**f;
	t_phil	**phil;

	memset(&v, 0, sizeof(t_var));
	if (check_args(&v, argc, argv) || argc < 2 || argc > 6)
		return (errno);
	f = init_forks(&v);
	if (!f)
		return (errno);
	phil = init_phil(&v);
	if (!phil)
		return (errno);
	if (init_variables(&v, f, phil))
		return (errno);
	if (start_threads(&v, phil))
	{
		free_mem(v.array_of_mallocs, v.counter_of_mallocs);
		return (errno);
	}
	free_mem(v.array_of_mallocs, v.counter_of_mallocs);
	return (0);
}
