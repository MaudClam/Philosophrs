/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:27:18 by mclam             #+#    #+#             */
/*   Updated: 2021/08/29 12:27:18 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void    ft_swap(long *a, long *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

/*
** start of ft_atoi()
*/

static int	islonglong(unsigned long nbr, int sign)
{
	if (nbr >= LONG_LONG_MAX && sign > 0)
		return (-1);
	else if (nbr > LONG_LONG_MAX)
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
