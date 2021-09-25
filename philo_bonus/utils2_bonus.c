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

int	errmsg(char *str, int err)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(" (exit code: ", STDERR_FILENO);
	ft_putnbr_fd(err, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	return (err);
}

/*
** start of ft_atoi()
*/
static int	islonglong(unsigned long nbr, int sign)
{
	if (nbr >= LLONG_MAX && sign > 0)
		return (-1);
	else if (nbr > LLONG_MAX)
		return (0);
	return ((int)nbr);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' \
					|| c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long int	nbr;
	int					sign;
	int					i;

	nbr = 0;
	sign = 1;
	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (islonglong(nbr, sign) * sign);
}
/*
** end of ft_atoi()
*/
