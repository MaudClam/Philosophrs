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

void	print_msg(t_phil *phil, char *msg)
{
	pthread_mutex_lock(&phil->v->mutex_stdout);
	pthread_mutex_lock(&phil->v->mutex_stderr);
	printf("%s %d\n", msg, phil->id + 1);
	pthread_mutex_unlock(&phil->v->mutex_stderr);
	pthread_mutex_unlock(&phil->v->mutex_stdout);

}
