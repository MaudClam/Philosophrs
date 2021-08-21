/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:21:19 by mclam             #+#    #+#             */
/*   Updated: 2021/08/21 17:21:19 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(t_phil *ph)
{
	printf("Hello from philosopher %d\n", ph->id + 1);
	sleep(10);
	printf("Hello1 from philosopher %d\n", ph->id + 1);
	return (NULL);
}

int	start_threads(t_var *v, t_phil **phil, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < v->number_of_philosophers)
	{
		if (i == TEST_FALED_TO_CREATE_THREAD || \
			pthread_create(&th[i], NULL, (void *)&philosopher, phil[i]))
		{
			errmsg("Faled to create thread", errno);
			break;
		}
		i++;
	}
	i = 0;
	while (i < v->number_of_philosophers)
	{
		if (pthread_detach(th[i]))
		{
			errmsg_clrmem("Faled to detach thread", errno, v, phil);
			return (-1);
		}
		i++;
	}
	return (0);
}
