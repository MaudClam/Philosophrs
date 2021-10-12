/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 20:32:03 by mclam             #+#    #+#             */
/*   Updated: 2021/09/01 02:22:50 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	game_over(t_var *v, t_phil **phil)
{
	int		i;
	int		counter;

	while (v->phnu)
	{
		timer(START_COUNTING);
		i = 0;
		counter = 0;
		while (i < v->phnu)
		{
			pthread_mutex_lock(&phil[i]->mutex_t_eat);
			counter += phil[i]->thread_compltd;
			pthread_mutex_unlock(&phil[i]->mutex_t_eat);
			i++;
		}
		if (counter == v->phnu)
		{
			if (phil[0]->v->num_of_times_each_phil_must_eat == 0)
				ft_putstr_fd(MSG_GAME_OVER_RED, STDOUT_FILENO);
			else
				ft_putstr_fd(MSG_GAME_OVER_GREEN, STDOUT_FILENO);
			return ;
		}
		timer(MONITORING_INTERVAL);
	}
}

void	it_is_death(time_t time, t_phil *phil)
{
	phil->v->num_of_times_each_phil_must_eat = 0;
	pthread_mutex_lock(&phil->v->mutex_stdout);
	ft_putnbr_fd((int)(time / 1000), STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(phil->id, STDOUT_FILENO);
	ft_putstr_fd(MSG_DIED, STDOUT_FILENO);
	pthread_mutex_unlock(&phil->v->mutex_stdout);
}

void	print_msg(time_t time, t_phil *phil, char *msg)
{
	if (phil->v->num_of_times_each_phil_must_eat != 0 && \
		time - phil->time_last_ate <= phil->v->time_to_die)
	{
		pthread_mutex_lock(&phil->v->mutex_stdout);
		ft_putnbr_fd((int)(time / 1000), STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putnbr_fd(phil->id, STDOUT_FILENO);
		ft_putstr_fd(msg, STDOUT_FILENO);
		pthread_mutex_unlock(&phil->v->mutex_stdout);
	}
}
