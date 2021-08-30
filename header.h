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
#  define NUMBER_OF_MALLOCS	6
# endif

# ifndef NUMBER_OF_MUTEXES
#  define NUMBER_OF_MUTEXES v->number_of_philosophers * 2 + 1
# endif

# ifndef MAX_NUM_OF_THREADS
#  define MAX_NUM_OF_THREADS INT_MAX
# endif

# ifndef INTERVAL_OF_DEATH_MONITORING
#  define INTERVAL_OF_DEATH_MONITORING 500
# endif

# define N						v->number_of_philosophers
# define N_						phil->v->number_of_philosophers
# define LEFT					(i + N_ - 1) % N_
# define RIGHT					i
# define TRUE					1
# define FALSE					0
# define MSG_TAKEN_FORK			"\033[33m has taken a fork\033[0m\n"
# define MSG_EATING				"\033[32m is eating\033[0m\n"
# define MSG_SLEEPING			"\033[37m is sleeping\033[0m\n"
# define MSG_THINKING			"\033[36m is thinking\033[0m\n"
# define MSG_DIED				"\033[31m is died\033[0m\n"
# define MSG_GAME_OVER_RED		"\033[31m====GAME OVER!====\033[0m\n"
# define MSG_GAME_OVER_GREEN	"\033[32m====GAME OVER!====\033[0m\n"
# define MSG_BAD_ARGUMENTS		"\033[1mBad arguments\033[0m\nusage:\
\t\033[1mphilo\033[0m number_of_philosophers time_to_die time_to_eat \
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
For more details, see: https://profile.intra.42.fr/searches\n"

typedef struct s_var			t_var;
typedef struct s_fork			t_fork;
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
	int				counter_of_mutexes;
	pthread_mutex_t	mutex_stdout;	/* Stdout area entry mutual exclusion     */
};

struct				s_fork
{
	pthread_mutex_t	mutex_fork;		/* One mutex for each fork                */
};

struct				s_phil
{
	int				i;				/* Philosopher's index (0, 1, ..., N-1)   */
	int				id;				/* Philosopher's id (1, 2,..., N)         */
	long			time_start;		/* Start time of all threads              */
	long			meal;			/* Philosopher's meal                     */
	long			belly;			/* Philosopher's belly                    */
	long			feces;			/* Philosopher's feces                    */
	int				eat_counter;	/* Philosopher's eats Counter             */
	long			time_last_ate;	/* Philosopher's time ate the last time   */
	char			thread_compltd;	/* The philosopher finished the game      */
	pthread_mutex_t	mutex_t_eat;	/* Time_last_ate area entry exclusion     */
	pthread_t		th;				/* Philosopher's thread                   */
	t_var			*v;				/* Pointer to array of variables          */
	t_fork			**f;			/* Pointer to state of a philosopher      */
};
/*
**		Philosopher functions, philo.c
*/
void	*philosopher(t_phil *phil);
int		take_forks(int i, t_phil *phil);
int		put_forks(int i, t_phil *phil);
int		eating(t_phil *phil);
int		sleeping(t_phil *phil);
/*
**		Philosopher functions, philo1.c
*/
void	print_msg(long time, t_phil *phil, char *msg);
long	get_time(long start);
void	it_is_death(long time, t_phil *phil);
void	game_over(t_var *v, t_phil **phil);
/*
**		Thread functions, threads.c
*/
int		start_threads(t_var *v, t_phil **phil);
int		init_mutexes(t_var *v, t_phil **phil);
int		init_mutex(void **a, int a_size, int *counter, pthread_mutex_t *mutex);
int		detach_threads(t_var *v, t_phil **phil, int counter);
int		death_monitor(t_var *v, t_phil **phil);
/*
**		Initialization functions, main.c
*/
int		check_args(t_var *v, int argc, char **argv);
t_fork	**init_forks(t_var *v);
t_phil	**init_phil(t_var *v);
int		 init_variables(t_var *v, t_fork **s, t_phil **phil);
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
/*
**		Secondary functions, utils2.c
*/
void    ft_swap(long *a, long *b);
int		ft_atoi(const char *str);

#endif
