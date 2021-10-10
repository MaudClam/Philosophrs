/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:02:18 by mclam             #+#    #+#             */
/*   Updated: 2021/09/01 02:22:27 by mclam            ###   ########.fr       */
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
#  define NUMBER_OF_MALLOCS		6
# endif

# ifndef TIME_DELAY
#  define TIME_DELAY 			50
# endif

# ifndef PHIL_TIMER_PRECISION
#  define PHIL_TIMER_PRECISION 	200
# endif

# ifndef MONITORING_INTERVAL
#  define MONITORING_INTERVAL 	5000
# endif

# ifndef FIND_TIMEDEATH_PRECSN
#  define FIND_TIMEDEATH_PRECSN	5000
# endif

# define START_COUNTING			0
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
	int				phnu;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_of_times_each_phil_must_eat;
	time_t			time_start_game;
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
	int				eat_counter;
	time_t			time_last_ate;
	char			thread_compltd;
	int				first;
	int				seccond;
	pthread_mutex_t	mutex_t_eat;
	pthread_t		th;
	t_var			*v;
	t_fork			**f;
};
/*
**		Initialization functions, main.c
*/
int		check_args(t_var *v, int argc, char **argv);
t_fork	**init_forks(t_var *v);
t_phil	**init_phil(t_var *v);
int		init_variables(t_var *v, t_fork **s, t_phil **phil);
/*
**		Philosopher functions, philo.c
*/
void	*philosopher(t_phil *phil);
int		take_forks(t_phil *phil);
void	put_forks(t_phil *phil);
int		eating(t_phil *phil);
void	sleeping(t_phil *phil);
/*
**		Philosopher functions, philo1.c
*/
void	game_over(t_var *v, t_phil **phil);
void	it_is_death(time_t time, t_phil *phil);
void	print_msg(time_t time, t_phil *phil, char *msg);
/*
**		Thread functions, threads.c
*/
int		start_threads(t_var *v, t_phil **phil);
int		init_mutexes(t_var *v, t_phil **phil);
int		init_mutex(void **a, int a_size, int *counter, pthread_mutex_t *mutex);
void	detach_threads(t_var *v, t_phil **phil, int counter);
void	death_monitor(t_var *v, t_phil **phil);
/*
**		Time functions, time.c
*/
time_t	getime(time_t start);
void	timer(useconds_t dt);
void	phil_timer(time_t time_start_game, time_t t1, time_t dt);
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
int		ft_atoi(const char *str);
int		msg_bad_arguments(void);

#endif
