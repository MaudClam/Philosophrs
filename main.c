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

//void	*philosopher(t_phil *ph)
//{
//	ph->id = 77;
//	return (NULL);
//}

int	init_varbls(t_var *v, t_phil_state **s, t_phil **phil, void *mutex)
{
	int	i;

	if (pthread_mutex_init(mutex, NULL))
	{
		free_mem(v);
		return (-1);
	}
	i = 0;
	while (i < v->number_of_philosophers)
	{
		phil[i]->id = i;
		phil[i]->s_pt = s;
		phil[i]->mutex = mutex;
		phil[i]->v_pt = v;
		if (pthread_mutex_init(&phil[i]->s_pt[i]->mutex_s, NULL))
		{
			destroy_mutexes(phil, i);
			free_mem(v);
			return (-2);
		}
		i++;
	}
	return (0);
}

t_phil	**init_phil(t_var *v)
{
	t_phil	*phil;
	t_phil	**phil_pt;
	int		i;

	phil = my_malloc(v, sizeof(t_phil) * v->number_of_philosophers);
	if (!phil)
		return (NULL);
	memset(phil, 0, sizeof(t_phil) * v->number_of_philosophers);
	phil_pt = my_malloc(v, sizeof(t_phil *) * (v->number_of_philosophers + 1));
	if (!phil_pt)
		return (NULL);
	i = v->number_of_philosophers;
	phil_pt[i] = NULL;
	while (i--)
		phil_pt[i] = &phil[i];
	return (phil_pt);
}

t_phil_state	**init_phil_state(t_var *v)
{
	t_phil_state	*s;
	t_phil_state	**s_pt;
	int				i;

	s = my_malloc(v, sizeof(t_phil_state) * v->number_of_philosophers);
	if (!s)
		return (NULL);
	memset(s, 0, sizeof(t_phil) * v->number_of_philosophers);
	s_pt = my_malloc(v, sizeof(t_phil_state *) * (v->number_of_philosophers + 1));
	if (!s_pt)
		return (NULL);
	i = v->number_of_philosophers;
	s_pt[i] = NULL;
	while (i--)
		s_pt[i] = &s[i];
	return (s_pt);
}

int	check_args(t_var *v)// The main() arguments will be added
{
	memset(v, 0, sizeof(t_var));
	v->number_of_philosophers = 4;
	v->time_to_die = 500;
	v->time_to_eat = 10;
	v->time_to_sleep = 80;
	v->number_of_times_each_philosopher_must_eat = 500;
	return (0);
}

int main()
{
	t_var			v;
	t_phil_state	**s;
	t_phil			**phil;
	pthread_mutex_t	mutex;
	pthread_t		*th;

	if (check_args(&v))// The main() arguments will be added
		return (err_msg("check_args() error in main()", errno));
	s = init_phil_state(&v);
	if (!s)
		return (err_msg("init_phil_state() error in main()", errno));
	phil = init_phil(&v);
	if (!phil)
		return (err_msg("init_phil() error in main()", errno));
	th = my_malloc(&v, sizeof(pthread_t) * v.number_of_philosophers);
	if (!th)
		return (err_msg("my_malloc() error in main()", errno));
	if (init_varbls(&v, s, phil, &mutex))
		return (err_msg("init_vars() error in main()", errno));
	start_threads(&v, phil, th);
	destroy_mutexes(phil, v.number_of_philosophers);
	free_mem(&v);
	return (0);
}
