/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:02:18 by mclam             #+#    #+#             */
/*   Updated: 2021/08/17 15:02:18 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>

# ifndef NUMBER_OF_MALLOCS
#  define NUMBER_OF_MALLOCS 0
# endif

//# define LEFT		(ph.id + c.number_of_philosophers) % (c.number_of_philosophers + 1)
//# define RIGHT		(id + 1) % (c.number_of_philosophers + 1)
# define YES			1
# define NO				0
# define SLEEPING		0
# define THINKING		1
# define EATING			2

typedef struct s_var		t_var;
typedef struct s_phil_state	t_phil_state;
typedef struct s_phil		t_phil;

struct		s_var
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	void	*mem[NUMBER_OF_MALLOCS];
	int		count_of_mallocs;

};

struct		s_phil_state
{
	char			state;		/* State of a philosopher: 0, 1 or 2 */
	pthread_mutex_t	mutex_s;	/* One semaphore for each philosopher */
};

struct		s_phil
{
	int				id;		/* Philosopher's id */
	t_phil_state	**s_pt;	/* Pointer to state of a philosopher: 0, 1 or 2 */
	pthread_mutex_t	*mutex;	/* Critical area entry mutual exclusion */
	t_var			*v_pt;	/* Pointer to array of variables */
	int				number_of_times_the_philosopher_ate;
};

void	*my_malloc(t_var *v, size_t size);
void	free_mem(t_var *v);
int		err_msg(char *str, int err);
void	destroy_mutexes(t_phil **phil, int i);

int	start_threads(t_var *v, t_phil **phil, pthread_t *th);

size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//pthread_mutex_t	mutex; //взаимное исключение входа в критическую область

#endif
