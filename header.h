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
# include <sys/time.h>
# include <limits.h>

# ifndef NUMBER_OF_MALLOCS
#  define NUMBER_OF_MALLOCS 6
# endif

# ifndef NUMBER_OF_MUTEXES
#  define NUMBER_OF_MUTEXES v->number_of_philosophers + 3
# endif

# ifndef MAX_NUM_OF_THREADS
#  define MAX_NUM_OF_THREADS INT_MAX
# endif

# define N				phil->v->number_of_philosophers
# define LEFT			(i + N - 1) % N
# define RIGHT			(i + 1) % N
# define YES			1
# define NO				0
# define TRUE			1
# define FALSE			0
# define SLEEPING		0
# define THINKING		1
# define HUNGRY			2
# define EATING			3
# define MSG_TAKEN_FORK	\033[33m has taken a fork\033[0m\n
# define MSG_EATING		\033[32m is eating\033[0m\n
# define MSG_SLEEPING	\033[37m is sleeping\033[0m\n
# define MSG_THINKING	\033[35m is thinking\033[0m\n
# define MSG_DIED		\033[31m is died\033[0m\n

typedef struct s_var			t_var;
typedef struct s_phil_status	t_phil_status;
typedef struct s_phil			t_phil;

struct				s_var
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	void			**array_of_mallocs;
	int				counter_of_mallocs;
	void			**array_of_mutexes;
	int				count_of_mutexes;
	pthread_mutex_t	mutex_exclsn;	/* Critical area entry mutual exclusion   */
	pthread_mutex_t	mutex_stdout;	/* Stdout area entry mutual exclusion     */
	pthread_mutex_t	mutex_stderr;	/* Stderr area entry mutual exclusion     */
};

struct				s_phil_status
{
	char			state;			/* State of a philosopher                 */
	pthread_mutex_t	mutex_state;	/* One semaphore for each philosopher     */
};

struct				s_phil
{
	int				id;				/* Philosopher's id                       */
	pthread_t		th;				/* Philosopher's thread                   */
	t_var			*v;				/* Pointer to array of variables          */
	t_phil_status	**s;			/* Pointer to state of a philosopher      */
	int				number_of_times_the_philosopher_ate;
};
/*
**		Philosopher functions, philo.c
*/
void	*philosopher(t_phil *phil);
void	take_forks(int i, t_phil *phil);
void	put_forks(int i, t_phil *phil);
void	test(int i, t_phil *phil);
void	print_msg(t_phil *phil, char *msg);
/*
**		Thread functions, threads.c
*/
int		start_threads(t_var *v, t_phil **phil);
int		init_mutexes(t_var *v, t_phil **phil);
int		init_mutex(void **a, int a_size, int *counter, pthread_mutex_t *mutex);
int		detach_threads(t_var *v, t_phil **phil, int counter);
/*
**		Initialization functions, main.c
*/
int				check_args(t_var *v);
t_phil_status	**init_phil_status(t_var *v);
t_phil			**init_phil(t_var *v);
int				init_varbls(t_var *v, t_phil_status **s, t_phil **phil);
/*
**		Malloc service and exit functions, utils.c
*/
void	*smart_calloc(void **a, int a_size, int *counter, size_t mem_size);
void	free_mem(void **a, int counter);
void	destroy_mutexes(void **a, int counter);
int		errmsg(char *str, int err);
int		errmsg_mutex(char *str, int err, t_var *v);
/*
**		Secondary functions, utils1.c
*/
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
