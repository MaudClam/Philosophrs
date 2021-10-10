/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:01:14 by mclam             #+#    #+#             */
/*   Updated: 2021/09/01 02:22:35 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_variables(t_var *v, t_fork **f, t_phil **phil)
{
	int	i;

	i = 0;
	while (i < v->phnu)
	{
		phil[i]->i = i;
		phil[i]->id = i + 1;
		phil[i]->first = (i + v->phnu - 1) % v->phnu;
		phil[i]->seccond = i;
		phil[i]->v = v;
		phil[i]->f = f;
		i++;
	}
	v->array_of_mutexes = smart_calloc(v->array_of_mallocs, \
								NUMBER_OF_MALLOCS, &v->counter_of_mallocs, \
								sizeof(pthread_mutex_t) * (v->phnu * 2 + 1));
	if (!v->array_of_mutexes)
		return (errmsg("smart_calloc()[5] error in  init_variables()", ERROR));
	return (SUCCESS);
}

t_phil	**init_phil(t_var *v)
{
	t_phil	*phil;
	t_phil	**phil_pt;
	int		i;

	phil = smart_calloc(v->array_of_mallocs, NUMBER_OF_MALLOCS, \
							&v->counter_of_mallocs, sizeof(t_phil) * v->phnu);
	if (!phil)
	{
		errmsg("smart_calloc()[3] error in init_phil()", ERROR);
		return (NULL);
	}
	phil_pt = smart_calloc(v->array_of_mallocs, NUMBER_OF_MALLOCS, \
					&v->counter_of_mallocs, sizeof(t_phil *) * (v->phnu + 1));
	if (!phil_pt)
	{
		errmsg("smart_calloc()[4] error in init_phil()", ERROR);
		return (NULL);
	}
	i = v->phnu;
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
					&v->counter_of_mallocs, sizeof(t_fork) * v->phnu);
	if (!s)
	{
		errmsg("smart_calloc()[1] error in init_forks()", ERROR);
		return (NULL);
	}
	pt_s = smart_calloc(v->array_of_mallocs, NUMBER_OF_MALLOCS, \
					&v->counter_of_mallocs, sizeof(t_fork *) * (v->phnu + 1));
	if (!pt_s)
	{
		errmsg("smart_calloc()[2] error in init_forks()", ERROR);
		return (NULL);
	}
	i = v->phnu;
	pt_s[i] = NULL;
	while (i--)
		pt_s[i] = &s[i];
	return (pt_s);
}

int	check_args(t_var *v, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (msg_bad_arguments());
	v->phnu = ft_atoi(argv[1]);
	if (v->phnu < 1 || v->phnu > 200)
		return (msg_bad_arguments());
	v->time_to_die = ft_atoi(argv[2]) * 1000;
	if (v->time_to_die < 60000)
		return (msg_bad_arguments());
	v->time_to_eat = ft_atoi(argv[3]) * 1000;
	if (v->time_to_eat < 60000)
		return (msg_bad_arguments());
	v->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (v->time_to_sleep < 60000)
		return (msg_bad_arguments());
	v->num_of_times_each_phil_must_eat = INT_MAX;
	if (argc == 6)
		v->num_of_times_each_phil_must_eat = ft_atoi(argv[5]);
	if (v->num_of_times_each_phil_must_eat < 1)
		return (msg_bad_arguments());
	v->array_of_mallocs = smart_calloc(NULL, NUMBER_OF_MALLOCS, \
					&v->counter_of_mallocs, sizeof(void *) * NUMBER_OF_MALLOCS);
	if (!v->array_of_mallocs)
		return (errmsg("smart_calloc()[0] error in check_args()", ERROR));
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_var	v;
	t_fork	**f;
	t_phil	**phil;

	memset(&v, 0, sizeof(t_var));
	if (check_args(&v, argc, argv) == ERROR)
		return (ERROR);
	f = init_forks(&v);
	if (!f)
		return (ERROR);
	phil = init_phil(&v);
	if (!phil)
		return (ERROR);
	if (init_variables(&v, f, phil) == ERROR)
		return (ERROR);
	if (start_threads(&v, phil) == ERROR)
	{
		free_mem(v.array_of_mallocs, v.counter_of_mallocs);
		return (ERROR);
	}
	free_mem(v.array_of_mallocs, v.counter_of_mallocs);
	return (0);
}
