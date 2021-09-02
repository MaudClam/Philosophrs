/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:34:05 by mclam             #+#    #+#             */
/*   Updated: 2021/08/18 17:34:05 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	errmsg_mutex(char *str, int err, t_var *v)
{
//	pthread_mutex_lock(&v->mutex_stdout);
	errmsg(str, err);
	pthread_mutex_unlock(&v->mutex_stdout);
	return (err);
}

int	errmsg(char *str, int err)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(" (exit code: ", STDERR_FILENO);
	ft_putnbr_fd(err, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	return (err);
}

void	destroy_mutexes(void **a, int counter)
{
	while (a && counter--)
	{
		if (a[counter])
		{
			pthread_mutex_destroy(a[counter]);
			a[counter] = NULL;
		}
	}
}

void	free_mem(void **a, int counter)
{
	while (a && counter--)
	{
		free(a[counter]);
		if (counter)
			a[counter] = NULL;
	}
}

void	*smart_calloc(void **a, int a_size, int *counter, size_t mem_size)
{
	void	*ptr;
	char	*b;

	ptr = NULL;
	if (*counter < a_size)
	{
		ptr = malloc(mem_size);
		if (!ptr)
			free_mem(a, *counter);
		else
		{
			if (!a)
				a = ptr;
			b = ptr;
			while (mem_size--)
				*(b++) = 0;
			a[*counter] = ptr;
			(*counter)++;
		}
	}
	else
		free_mem(a, *counter);
	return (ptr);
}
