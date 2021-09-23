/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:02:18 by mclam             #+#    #+#             */
/*   Updated: 2021/09/22 00:31:09 by mclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>


# ifndef NUMBER_OF_MALLOCS
#  define NUMBER_OF_MALLOCS	6
# endif

# ifndef TEST_NUM_OF_THREADS
#  define TEST_NUM_OF_THREADS INT_MAX
# endif

# ifndef TIME_INTERVAL
#  define TIME_INTERVAL 500
# endif

# define TRUE					1
# define FALSE					0
# define ERROR					-1
# define SUCCESS				0
# define GAME_OVER				200
# define MSG_TAKEN_FORK			"\033[33m has taken a fork\033[0m\n"
# define MSG_EATING				"\033[32m is eating\033[0m\n"
# define MSG_SLEEPING			"\033[37m is sleeping\033[0m\n"
# define MSG_THINKING			"\033[36m is thinking\033[0m\n"
# define MSG_DIED				"\033[31m is died\033[0m\n"
# define MSG_GAME_OVER_RED		"\033[31m====GAME OVER!====\033[0m\n"
# define MSG_GAME_OVER_GREEN	"\033[32m====GAME OVER!====\033[0m\n"

typedef struct s_var			t_var;
typedef struct s_fork			t_fork;
typedef struct s_phil			t_phil;

struct				s_var
{
	int				pnu;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	time_t			time_start;
	void			**array_of_mallocs;
	int				counter_of_mallocs;
	void			**array_of_mutexes;
	int				counter_of_mutexes;
	pthread_mutex_t	mutex_stdout;
};

struct				s_fork
{
	pthread_mutex_t	mutex_fork;
};

struct				s_phil
{
	int				i;
	int				id;
	long			meal;
	long			belly;
	long			feces;
	int				eat_counter;
	time_t			time_last_ate;
	char			thread_compltd;
	pthread_mutex_t	mutex_t_eat;
	pthread_t		th;
	t_var			*v;
	t_fork			**f;
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
void	print_msg(time_t time, t_phil *phil, char *msg);
time_t	getime(time_t start);
void	it_is_death(time_t time, t_phil *phil);
void	game_over(t_var *v, t_phil **phil);
int		left(int right, int n);
/*
**		Thread functions, threads.c
*/
int		start_threads(t_var *v, t_phil **phil);
int		init_mutexes(t_var *v, t_phil **phil);
int		init_mutex(void **a, int a_size, int *counter, pthread_mutex_t *mutex);
void	detach_threads(t_var *v, t_phil **phil, int counter);
void	death_monitor(t_var *v, t_phil **phil);
/*
**		Initialization functions, main.c
*/
int		check_args(t_var *v, int argc, char **argv);
t_fork	**init_forks(t_var *v);
t_phil	**init_phil(t_var *v);
int		init_variables(t_var *v, t_fork **s, t_phil **phil);
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
void	ft_swap(time_t *a, time_t *b);
int		ft_atoi(const char *str);
int		msg_bad_arguments(void);

#endif