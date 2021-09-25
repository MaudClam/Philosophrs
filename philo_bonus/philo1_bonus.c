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

void	print_msg(time_t time, t_var *v, char *msg, char *color)
{
	sem_wait(v->sem_stdout);
	ft_putstr_fd(color, STDOUT_FILENO);
	ft_putnbr_fd((int)time, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(v->phil_id, STDOUT_FILENO);
	ft_putstr_fd(msg, STDOUT_FILENO);
	ft_putstr_fd(DEFAULT_COLOR, STDOUT_FILENO);
	sem_post(v->sem_stdout);
}

void	print_msg_died_and_exit(time_t time, t_var *v, int err)
{
	sem_wait(v->sem_stdout);
	ft_putstr_fd(RED, STDOUT_FILENO);
	ft_putnbr_fd((int)time, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(v->phil_id, STDOUT_FILENO);
	ft_putstr_fd(MSG_DIED, STDOUT_FILENO);
	ft_putstr_fd(DEFAULT_COLOR, STDOUT_FILENO);
	free_mem(v);
	exit(err);
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
