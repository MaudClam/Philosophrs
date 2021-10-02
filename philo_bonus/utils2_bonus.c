/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:27:18 by mclam             #+#    #+#             */
/*   Updated: 2021/09/25 07:02:13 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

int	msg_bad_arguments(int err)
{
	ft_putstr_fd("\033[1mBad arguments\033[0m\nusage:\
\t\033[1mphilo_bonus\033[0m number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n\n\
\t\033[1mnumber_of_philosophers\033[0m - number of philosophers from 1 to 200\n\
\t\033[1mtime_to_die\033[0m - time in milliseconds from 60 to INT_MAX\n\
\t\033[1mtime_to_eat\033[0m - time in milliseconds from 60 to INT_MAX\n\
\t\033[1mtime_to_sleep\033[0m - time in milliseconds from 60 to INT_MAX\n\
\t\033[1m[number_of_times_each_philosopher_must_eat]\033[0m - from 1 to \
INT_MAX\n\n\033[1mPhilo\033[0m is an emulator of the classic \033[1mDining \
Philosophers Problem\033[0m used in computer science to illustrate \
synchronization problems.\n\
The tutorial project was written by Maud Clam [mclam@student.21-school.ru] \
in pure C without a single nail.\n\
For more details: https://profile.intra.42.fr/searches\n\n", STDOUT_FILENO);
	return (err);
}

void	print_msg(time_t time, t_var *v, char *msg, char *color)
{
	if (getime(v->time_start) - v->time_last_ate < v->time_to_die)
	{
		sem_wait(v->sem_stdout);
		printf("%s%ld %d %s"DEFAULT, color, time, v->phil_id, msg);
		sem_post(v->sem_stdout);
	}
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

char	*indexname(char const *name, int index)
{
	char	*str;
	int		len;
	int		i;
	
	if (index < 1)
		return ((char *)name);
	len = (int)ft_strlen(name) + 1;
	i = index;
	while (i > 9 && ++len)
		i /= 10;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (name && name[++i])
		str[i] = name[i];
	str[len] = '\0';
	while (len-- && index)
	{
		str[len] = index % 10 + '0';
		index /= 10;
	}
	return (str);
}

time_t	getime(time_t start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000 - start);
}
