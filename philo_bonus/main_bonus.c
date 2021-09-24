/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 03:05:38 by mclam             #+#    #+#             */
/*   Updated: 2021/09/22 03:05:52 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	start_processes(t_var *v)
{
	int	status;
	
	status = 0;
	v->pids[0] = getpid();
	v->time_start = getime(0);
	while (v->phil_id++ < v->num_of_phils)
	{
		v->pids[v->phil_id] = fork();
		if (v->pids[v->phil_id] == ERROR)
			exit(errmsg("fork() call error in start_processes()", errno));
		else if (v->pids[v->phil_id] == SUCCESS)
			philosopher(v);
		else
			usleep(TIME_INTERVAL);
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) == 0)
	{
		printf(MSG_GAME_OVER_GREEN);
		while (v->phil_id)
			kill(v->pids[v->phil_id--], SIGKILL);
	}
}

void	open_semaphores(t_var *v)
{
	v->sem_forks = sem_open("forks", O_CREAT, S_IRWXU, \
												(unsigned int)v->num_of_phils);
	if (v->sem_forks == SEM_FAILED)
	{
		v->sem_forks = NULL;
		free_mem(v);
		exit(errmsg("sem_open()[0] error in open_semaphores()", ERROR));
	}
	v->sem_stdout = sem_open("stdout", O_CREAT);
	if (v->sem_stdout == SEM_FAILED)
	{
		v->sem_forks = NULL;
		free_mem(v);
		exit(errmsg("sem_open()[1] error in open_semaphores()", ERROR));
	}
}

void	free_mem(t_var *v)
{
	free(v->pids);
	if (v->sem_forks)
	{
		if (sem_close(v->sem_forks) == EINVAL)
			errmsg("v->sem_forks is not a valid semaphore descriptor", errno);
		if (sem_unlink("forks") != SUCCESS)
			errmsg("sem_unlink(\"forks\") error in free_mem()", errno);
	}
	if (v->sem_stdout)
	{
		if (sem_close(v->sem_stdout) == EINVAL)
			errmsg("v->sem_stdout is not a valid semaphore descriptor",errno);
		if (sem_unlink("stdout") != SUCCESS)
			errmsg("sem_unlink(\"stdout\") error in free_mem()",errno);
	}
}

int	check_args(t_var *v, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (msg_bad_arguments());
	v->num_of_phils = ft_atoi(argv[1]);
	if (v->num_of_phils < 1 || v->num_of_phils > 200)
		return (msg_bad_arguments());
	v->time_to_die = ft_atoi(argv[2]);
	if (v->time_to_die < 60)
		return (msg_bad_arguments());
	v->time_to_eat = ft_atoi(argv[3]);
	if (v->time_to_eat < 60)
		return (msg_bad_arguments());
	v->time_to_sleep = ft_atoi(argv[4]);
	if (v->time_to_sleep < 60)
		return (msg_bad_arguments());
	v->num_of_times_each_phil_must_eat = INT_MAX;
	if (argc == 6)
		v->num_of_times_each_phil_must_eat = ft_atoi(argv[5]);
	if (v->num_of_times_each_phil_must_eat < 1)
		return (msg_bad_arguments());
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_var	v;

	memset(&v, 0, sizeof(t_var));
	if (check_args(&v, argc, argv) == ERROR)
		exit(ERROR);
	v.pids = (pid_t *)malloc(sizeof(pid_t) * (v.num_of_phils + 1));
	if (!v.pids)
		exit(errmsg("malloc() error in main_bonus()", errno));
	memset(v.pids, 0, sizeof(pid_t) * (v.num_of_phils + 1));
	start_processes(&v);
	free_mem(&v);
	exit(SUCCESS);
}
