/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 20:32:03 by mclam             #+#    #+#             */
/*   Updated: 2021/08/25 20:32:03 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	game_over(t_var *v, t_phil **phil)
{
	int		i;
	int		counter;

	while (TRUE)
	{
		usleep(INTERVAL_OF_DEATH_MONITORING);
		i = 0;
		counter = 0;
		while (i < N)
		{
			pthread_mutex_lock(&phil[i]->mutex_t_eat);
			counter += phil[i]->thread_compltd;
			pthread_mutex_unlock(&phil[i]->mutex_t_eat);
			i++;
		}
		if (counter == N)
		{
			if (phil[0]->v->number_of_times_each_philosopher_must_eat == 0)
				printf("%s", MSG_GAME_OVER_RED);
			else
				printf("%s", MSG_GAME_OVER_GREEN);
			return ;
		}
	}
}

void	it_is_death(long time, t_phil *phil)
{
	phil->v->number_of_times_each_philosopher_must_eat = 0;
	pthread_mutex_lock(&phil->v->mutex_stdout);
	printf("%ld %d%s", time, phil->id, MSG_DIED);
	pthread_mutex_unlock(&phil->v->mutex_stdout);
}

void	print_msg(long time, t_phil *phil, char *msg)
{
	if (phil->v->number_of_times_each_philosopher_must_eat != 0 && \
	 get_time(phil->time_start) - phil->time_last_ate < phil->v->time_to_die)
	{
		pthread_mutex_lock(&phil->v->mutex_stdout);
		printf("%ld %d%s", time, phil->id, msg);
		pthread_mutex_unlock(&phil->v->mutex_stdout);
	}
}

long	get_time(long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000 - start);
}
