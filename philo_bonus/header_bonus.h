/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:02:18 by mclam             #+#    #+#             */
/*   Updated: 2021/09/26 04:02:51 by mclam            ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>

# ifndef TIME_DELAY
#  define TIME_DELAY 		300
# endif

# ifndef MONITOR_DELAY
#  define MONITOR_DELAY 	1000
# endif

# define TRUE				1
# define FALSE				0
# define ERROR				-1
# define SUCCESS			0
# define OPEN				1
# define CLOSE				0
# define SEM_FORKS			"/forks"
# define SEM_STDOUT			"/stdout"
# define SEM_MONITOR		"/monitor_"
# define DEFAULT			"\033[0m"
# define YELLOW				"\033[33m"
# define GREEN				"\033[32m"
# define GRAY				"\033[37m"
# define TURQUOISE			"\033[36m"
# define RED				"\033[31m"
# define MSG_TAKEN_FORK		"has taken a fork\n"
# define MSG_EATING			"is eating\n"
# define MSG_SLEEPING		"is sleeping\n"
# define MSG_THINKING		"is thinking\n"
# define MSG_DIED			"is died\n"
# define MSG_GAME_OVER		"====GAME OVER!====\n"

typedef struct s_var
{
	int			num_of_phils;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_times_each_phil_must_eat;
	int			phil_id;
	int			eat_counter;
	int			status;
	sem_t		*sem_forks;
	sem_t		*sem_stdout;
	sem_t		*sem_monitor;
	char		*sem_monitor_name;
	pid_t		*pids;
	time_t		time_start;
	time_t		time_start_eat;
	time_t		time_last_ate;
	pthread_t	th;
	char		thread_compltd;
}				t_var;

/*
**		philo_bonus.c
*/
void	*philosopher(t_var *v);
int		take_forks(t_var *v);
int		eating(t_var *v);
void	put_forks(t_var *v);
int		sleeping(t_var *v);
/*
**		philo1_bonus.c
*/
void	death_monitor(t_var *v);
void	death(t_var *v);
int		sem_monitor(t_var *v, char mode);
void	kill_phill(t_var *v, int signal);
int		free_mem(t_var *v, int err);
/*
**		main_bonus.c
*/
int		check_args(t_var *v, int argc, char **argv);
int		open_semaphores(t_var *v);
int		start_processes(t_var *v);
int		wait_phils_signals(t_var *v);
/*
**		utils1_bonus.c
*/
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
/*
**		utils2_bonus.c
*/
int		msg_bad_arguments(int err);
void	print_msg(time_t time, t_var *v, char *msg, char *color);
int		errmsg(char *str, int err);
char	*indexname(char const *name, int index);
time_t	getime(time_t start);

#endif
