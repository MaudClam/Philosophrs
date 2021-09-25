/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 03:05:38 by mclam             #+#    #+#             */
/*   Updated: 2021/09/25 07:00:43 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

int	wait_phils_signals(t_var *v)
{
	int	i;

	i = 0;
	while (i < v->num_of_phils)
	{
		if (waitpid(-1, &v->status, 0) != -1)
		{
			if (v->status != 0)
			{
				kill_phill(v);
				ft_putstr_fd(RED MSG_GAME_OVER DEFAULT_COLOR, STDOUT_FILENO);
				free_mem(v, ERROR);
				return (ERROR);
			}
			else
				i++;
		}
	}
	ft_putstr_fd(GREEN MSG_GAME_OVER DEFAULT_COLOR, STDOUT_FILENO);
	return (SUCCESS);
}

int	start_processes(t_var *v)
{
	v->time_start = getime(0);
	while (v->phil_id++ < v->num_of_phils)
	{
		v->pids[v->phil_id] = fork();
		if (v->pids[v->phil_id] == ERROR)
		{
			errmsg("fork() call error", errno);
			kill_phill(v);
			free_mem(v, ERROR);
			return (ERROR);
		}
		else if (v->pids[v->phil_id] == SUCCESS)
			philosopher(v);
		else
			usleep(TIME_INTERVAL);
	}
	return (SUCCESS);
}

int	open_semaphores(t_var *v)
{
	sem_unlink(SEM_FORKS);
	v->sem_forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, v->num_of_phils);
	if (v->sem_forks == SEM_FAILED)
	{
		errmsg("sem_open() error", errno);
		v->sem_forks = NULL;
		return (free_mem(v, ERROR));
	}
	sem_unlink(SEM_STDOUT);
	v->sem_stdout = sem_open(SEM_STDOUT, O_CREAT, S_IRWXU, 1);
	if (v->sem_stdout == SEM_FAILED)
	{
		errmsg("sem_open() error", errno);
		v->sem_stdout = NULL;
		return (free_mem(v, ERROR));
	}
	sem_unlink(SEM_MONITOR);
	v->sem_monitor = sem_open(SEM_MONITOR, O_CREAT, S_IRWXU, 1);
	if (v->sem_monitor == SEM_FAILED)
	{
		errmsg("sem_open() error", errno);
		v->sem_monitor = NULL;
		return (free_mem(v, ERROR));
	}
	return (SUCCESS);
}

int	check_args(t_var *v, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (msg_bad_arguments(ERROR));
	v->num_of_phils = ft_atoi(argv[1]);
	if (v->num_of_phils < 1 || v->num_of_phils > 200)
		return (msg_bad_arguments(ERROR));
	v->time_to_die = ft_atoi(argv[2]);
	if (v->time_to_die < 60)
		return (msg_bad_arguments(ERROR));
	v->time_to_eat = ft_atoi(argv[3]);
	if (v->time_to_eat < 60)
		return (msg_bad_arguments(ERROR));
	v->time_to_sleep = ft_atoi(argv[4]);
	if (v->time_to_sleep < 60)
		return (msg_bad_arguments(ERROR));
	v->num_of_times_each_phil_must_eat = INT_MAX;
	if (argc == 6)
		v->num_of_times_each_phil_must_eat = ft_atoi(argv[5]);
	if (v->num_of_times_each_phil_must_eat < 1)
		return (msg_bad_arguments(ERROR));
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_var	v;

	memset(&v, 0, sizeof(t_var));
	if (check_args(&v, argc, argv) == ERROR)
		exit(EXIT_FAILURE);
	v.pids = (pid_t *)malloc(sizeof(pid_t) * (v.num_of_phils + 1));
	if (!v.pids)
		exit(errmsg("malloc() error", EXIT_FAILURE));
	memset(v.pids, -1, sizeof(pid_t) * (v.num_of_phils + 1));
	if (open_semaphores(&v) == ERROR)
		exit(EXIT_FAILURE);
	if (start_processes(&v) == ERROR)
		exit(EXIT_FAILURE);
	if (wait_phils_signals(&v) == ERROR)
		exit(EXIT_FAILURE);
	free_mem(&v, SUCCESS);
	exit(EXIT_SUCCESS);
}
