/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:34:05 by mclam             #+#    #+#             */
/*   Updated: 2021/08/18 17:34:05 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	err_msg(char *str, int err)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(" (exit code: ", STDERR_FILENO);
	ft_putnbr_fd(err, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	return (err);
}

void	destroy_mutexes(t_phil **phil, int i)
{
	pthread_mutex_destroy((void *)phil[0]->mutex);
	while (--i >= 0)
		pthread_mutex_destroy(&phil[i]->s_pt[i]->mutex_s);
}

void	free_mem(t_var *v)
{
	int	i;
	
	i = 0;
	while (i < v->count_of_mallocs)
	{
		free(v->mem[i]);
		v->mem[i] = NULL;
		i++;
	}
}

void	*my_malloc(t_var *v, size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (v->count_of_mallocs < NUMBER_OF_MALLOCS)
	{
		ptr = malloc(size);
		if (!ptr)
			free_mem(v);
		else
		{
			v->mem[v->count_of_mallocs] = ptr;
			v->count_of_mallocs++;
		}
	}
	else
		free_mem(v);
	return (ptr);
}
