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
	start_thread(v);
	while (TRUE)
	{
		timer(START_COUNTING);
		sem_wait(v->sem_monitor);
		if ((getime(v->time_start) - v->time_last_ate) / FIND_TIMEDEATH_PRECSN \
			<= v->time_to_die / FIND_TIMEDEATH_PRECSN && \
			v->eat_counter == v->num_of_times_each_phil_must_eat && \
			v->thread_compltd == TRUE)
		{
			sem_post(v->sem_monitor);
			sem_monitor(v, CLOSE);
			exit(free_mem(v, EXIT_SUCCESS));
		}
		else if ((getime(v->time_start) - v->time_last_ate) / \
				 FIND_TIMEDEATH_PRECSN > v->time_to_die / FIND_TIMEDEATH_PRECSN)
		{
			sem_post(v->sem_monitor);
			death(v);
			sem_monitor(v, CLOSE);
			exit(free_mem(v, EXIT_FAILURE));
		}
		sem_post(v->sem_monitor);
		timer(MONITORING_INTERVAL);
	}
}

void	start_thread(t_var *v)
{
	if (sem_monitor(v, OPEN) == ERROR)
		exit(free_mem(v, EXIT_FAILURE));
	sem_wait(v->sem_stdout);
	v->time_start = getime(0);
	usleep(v->phil_id * TIME_DELAY);
	if (pthread_create(&v->th, NULL, (void *)&philosopher, v) != SUCCESS)
		exit(free_mem(v, errmsg("failed to create thread", errno)));
	pthread_detach(v->th);
}

int	sem_monitor(t_var *v, char mode)
{
	if (mode == OPEN)
	{
		v->sem_monitor_name = indexname(SEM_MONITOR, v->phil_id);
		if (!v->sem_monitor_name)
			return (errmsg("error creating sem_monitor_name", ERROR));
		sem_unlink(v->sem_monitor_name);
		v->sem_monitor = sem_open(v->sem_monitor_name, O_CREAT, S_IRWXU, 1);
		if (v->sem_monitor == SEM_FAILED)
		{
			errmsg("sem_open() error in sem_monitor()", errno);
			free(v->sem_monitor_name);
			return (ERROR);
		}
	}
	else
	{
		sem_post(v->sem_monitor);
		if (v->sem_monitor && sem_close(v->sem_monitor) == EINVAL)
			errmsg("v->sem_monitor is not a valid semaphore descriptor", errno);
		sem_unlink(v->sem_monitor_name);
		free(v->sem_monitor_name);
		usleep(MONITORING_INTERVAL);
		v->sem_monitor_name = NULL;
	}
	return (SUCCESS);
}

void	death(t_var *v)
{
	sem_wait(v->sem_stdout);
	ft_putnbr_fd((int)(getime(v->time_start) / 1000), STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(v->phil_id, STDOUT_FILENO);
	ft_putstr_fd(RED MSG_DIED DEFAULT, STDOUT_FILENO);
	sem_wait(v->sem_monitor);
	while (v->thread_compltd != TRUE)
	{
		sem_post(v->sem_monitor);
		usleep(MONITORING_INTERVAL);
		sem_wait(v->sem_monitor);
	}
	sem_post(v->sem_monitor);
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
