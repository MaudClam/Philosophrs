/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 20:32:03 by mclam             #+#    #+#             */
/*   Updated: 2021/09/25 07:00:58 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

time_t	getime(time_t start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000 - start);
}

int	free_mem(t_var *v, int err)
{
	free(v->pids);
	v->pids = NULL;
	if (v->sem_forks && sem_close(v->sem_forks) == EINVAL)
		errmsg("v->sem_forks is not a valid semaphore descriptor", errno);
	if (v->sem_stdout && sem_close(v->sem_stdout) == EINVAL)
		errmsg("v->sem_stdout is not a valid semaphore descriptor", errno);
	if (v->sem_monitor && sem_close(v->sem_monitor) == EINVAL)
		errmsg("v->sem_monitor is not a valid semaphore descriptor", errno);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_STDOUT);
	sem_unlink(SEM_MONITOR);
	return (err);
}

void	print_msg(time_t time, t_var *v, char *msg, char *color)
{
	sem_wait(v->sem_stdout);
	printf("%s%ld %d %s"DEFAULT_COLOR, color, time, v->phil_id, msg);
	sem_post(v->sem_stdout);
}

void	print_msg_died_and_exit(time_t time, t_var *v, int err)
{
	sem_wait(v->sem_stdout);
	printf(RED"%ld %d "MSG_DIED DEFAULT_COLOR, time, v->phil_id);
	err = 0;
//	sem_post(v->sem_stdout);
//	free_mem(v, err);
	exit(EXIT_FAILURE);
}

void	kill_phill(t_var *v)
{
	int	i;

	i = 1;
	while (i <= v->num_of_phils)
	{
		if (v->pids[i] > 1)
			if (kill(v->pids[i], SIGKILL) == SUCCESS)
				waitpid(v->pids[i], &v->status, WNOHANG);
		i++;
	}
}
