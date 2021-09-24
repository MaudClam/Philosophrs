/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 20:32:03 by mclam             #+#    #+#             */
/*   Updated: 2021/09/22 03:20:36 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	print_msg(time_t time, t_var *v, char *msg)
{
	sem_wait(v->sem_stdout);
	ft_putnbr_fd((int)time, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(v->phil_id, STDOUT_FILENO);
	ft_putstr_fd(msg, STDOUT_FILENO);
	sem_post(v->sem_stdout);
}

void	print_msg_died_and_exit(time_t time, t_var *v, int err)
{
	sem_wait(v->sem_stdout);
	ft_putnbr_fd((int)time, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(v->phil_id, STDOUT_FILENO);
	ft_putstr_fd(MSG_DIED, STDOUT_FILENO);
//	sem_post(v->sem_stdout);
	free_mem(v);
	exit(err);
}

time_t	getime(time_t start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000 - start);
}

void	kill_phill(t_var *v)
{
	int	i;
	
	i = 1;
	while (i <= v->num_of_phils)
	{
		if (v->pids[i] > 1)
		{
			if (kill(v->pids[i], SIGKILL) == SUCCESS)
			waitpid(v->pids[i], NULL, WNOHANG);
		}
		i++;
	}
}
