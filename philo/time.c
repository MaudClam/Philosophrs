/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 03:39:51 by mclam             #+#    #+#             */
/*   Updated: 2021/10/10 03:39:51 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

time_t	getime(time_t start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + tv.tv_usec - start);
}

void	timer(useconds_t dt)
{
	struct timeval		tv;
	static time_t		t1;

	gettimeofday(&tv, NULL);
	if (dt == START_COUNTING)
		t1 = tv.tv_sec * 1000000 + tv.tv_usec;
	else
	{
		while (tv.tv_sec * 1000000 + tv.tv_usec - t1 < dt)
		{
			if (!usleep(dt - \
						(useconds_t)(tv.tv_sec * 1000000 + tv.tv_usec - t1)))
				break ;
			gettimeofday(&tv, NULL);
		}
	}
}

void	phil_timer(time_t time_start_game, time_t t1, time_t dt)
{
	time_t	t2;

	t2 = getime(time_start_game);
	usleep((useconds_t)(dt - (t2 - t1)) / 10 * 8);
	t2 = getime(time_start_game);
	while (t2 - t1 < dt - PHIL_TIMER_PRECISION)
	{
		usleep(PHIL_TIMER_PRECISION);
		t2 = getime(time_start_game);
	}
}
