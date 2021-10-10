/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 20:32:03 by mclam             #+#    #+#             */
/*   Updated: 2021/09/26 04:02:27 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	death_monitor(t_var *v)
{
	if (sem_monitor(v, OPEN) != SUCCESS)
		exit(free_mem(v, errmsg("failed to open sem_monitor", EXIT_FAILURE)));
	sem_wait(v->sem_stdout);
	v->time_start = getime(0);
	usleep(v->phil_id * TIME_DELAY);
	if (pthread_create(&v->th, NULL, (void *)&philosopher, v) != SUCCESS)
		exit(free_mem(v, errmsg("failed to create thread", errno)));
	pthread_detach(v->th);
	while (TRUE)
	{
		sem_wait(v->sem_monitor);
		if (getime(v->time_start) - v->time_last_ate < v->time_to_die && \
			v->eat_counter == v->num_of_times_each_phil_must_eat && \
			v->thread_compltd == TRUE && sem_monitor(v, CLOSE) == SUCCESS)
			exit(free_mem(v, EXIT_SUCCESS));
		else if (getime(v->time_start) - v->time_last_ate >= v->time_to_die)
		{
			death(v);
			exit(free_mem(v, EXIT_FAILURE));
		}
		sem_post(v->sem_monitor);
		usleep(MONITOR_DELAY);
	}
}

void	death(t_var *v)
{
	sem_post(v->sem_monitor);
	sem_wait(v->sem_stdout);
	printf(RED"%ld %d "MSG_DIED DEFAULT, getime(v->time_start), v->phil_id);
	sem_post(v->sem_forks);
	sem_wait(v->sem_monitor);
	while (v->thread_compltd != TRUE)
	{
		sem_post(v->sem_monitor);
		usleep(TIME_DELAY);
		sem_wait(v->sem_monitor);
	}
	sem_post(v->sem_monitor);
	sem_monitor(v, CLOSE);
}

int	sem_monitor(t_var *v, char mode)
{
	if (mode == OPEN)
	{
		v->sem_monitor_name = indexname(SEM_MONITOR, v->phil_id);
		if (!v->sem_monitor_name)
			return (free_mem(v, errmsg("error sem_monitor_name", ERROR)));
		sem_unlink(v->sem_monitor_name);
		v->sem_monitor = sem_open(v->sem_monitor_name, O_CREAT, S_IRWXU, 1);
		if (v->sem_monitor == SEM_FAILED)
			return (errmsg("sem_open() error", errno));
	}
	else
	{
		sem_post(v->sem_monitor);
		if (v->sem_monitor && sem_close(v->sem_monitor) == EINVAL)
			errmsg("v->sem_monitor is not a valid semaphore descriptor", errno);
		sem_unlink(v->sem_monitor_name);
		free(v->sem_monitor_name);
		v->sem_monitor_name = NULL;
		usleep(MONITOR_DELAY);
	}
	return (SUCCESS);
}

void	kill_phill(t_var *v, int signal)
{
	int	i;

	i = 1;
	while (i <= v->phnu)
	{
		usleep(TIME_DELAY);
		if (v->pids[i] > 1)
		{
			kill(v->pids[i], signal);
			if (kill(v->pids[i], signal) == SUCCESS)
				waitpid(v->pids[i], &v->status, WNOHANG);
		}
		i++;
	}
}

int	free_mem(t_var *v, int err)
{
	free(v->pids);
	v->pids = NULL;
	if (v->sem_forks && sem_close(v->sem_forks) == EINVAL)
		errmsg("v->sem_forks is not a valid semaphore descriptor", errno);
	if (v->sem_garcon_no2 && sem_close(v->sem_garcon_no2) == EINVAL)
		errmsg("v->sem_garcon_no2 is not a valid semaphore descriptor", errno);
	if (v->sem_stdout && sem_close(v->sem_stdout) == EINVAL)
		errmsg("v->sem_stdout is not a valid semaphore descriptor", errno);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_STDOUT);
	return (err);
}
