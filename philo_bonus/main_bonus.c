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
	v->time_start = getime(0);
	while (v->phil_id++ < v->num_of_phils)
	{
		v->pids[v->phil_id] = fork();
		if (v->pids[v->phil_id] == ERROR)
		{
			errmsg("fork() call error in start_processes()", errno);
			kill_phill(v);
			return ;
		}
		else if (v->pids[v->phil_id] == SUCCESS)
			philosopher(v);
		else
			usleep(TIME_INTERVAL);
	}
	waitpid(-1, &v->status, 0);
	if (v->status != 0)
	{
		kill_phill(v);
		ft_putstr_fd(MSG_GAME_OVER_RED, STDOUT_FILENO);
	}
	else
	{
		sem_wait(v->sem_stdout);
		ft_putstr_fd(MSG_GAME_OVER_GREEN, STDOUT_FILENO);
		kill_phill(v);
//		sem_wait(v->sem_stdout);
	}
}

void	free_mem(t_var *v)
{
	free(v->pids);
	v->pids = NULL;
	if (v->sem_forks && sem_close(v->sem_forks) == EINVAL)
		errmsg("v->sem_forks is not a valid semaphore descriptor", errno);
	if (v->sem_stdout && sem_close(v->sem_stdout) == EINVAL)
		errmsg("v->sem_stdout is not a valid semaphore descriptor",errno);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_STDOUT);
}

void	open_semaphores(t_var *v)
{
	sem_unlink(SEM_FORKS);
	v->sem_forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, \
												(unsigned int)v->num_of_phils);
	if (v->sem_forks == SEM_FAILED)
	{
		v->sem_forks = NULL;
		free_mem(v);
		exit(errmsg("sem_open()[0] error in open_semaphores()", ERROR));
	}
	sem_unlink(SEM_STDOUT);
	v->sem_stdout = sem_open(SEM_STDOUT, O_CREAT, S_IRWXU, 1);
	if (v->sem_stdout == SEM_FAILED)
	{
		v->sem_forks = NULL;
		free_mem(v);
		exit(errmsg("sem_open()[1] error in open_semaphores()", ERROR));
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
	memset(v.pids, -1, sizeof(pid_t) * (v.num_of_phils + 1));
	open_semaphores(&v);
	start_processes(&v);
	free_mem(&v);
	exit(SUCCESS);
}
