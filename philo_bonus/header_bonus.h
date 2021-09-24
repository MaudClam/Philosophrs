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
# include <signal.h>


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

typedef struct	s_var
{
	int		num_of_phils;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_times_each_phil_must_eat;
	int		phil_id;
	int		eat_counter;
	pid_t	*pids;
	sem_t	*sem_forks;
	sem_t	*sem_stdout;
	time_t	time_last_ate;
	time_t	time_start;
}				t_var;

/*
**		philo_bonus.c
*/
int		philosopher(t_var *v);
int		take_forks(t_var *v);
void	put_forks(t_var *v);
int		eating(t_var *v);
int		sleeping(t_var *v);
/*
**		philo1_bonus.c
*/
void	print_msg(time_t time, t_var *v, char *msg);
time_t	getime(time_t start);
/*
**		main_bonus.c
*/
int		check_args(t_var *v, int argc, char **argv);
void	free_mem(t_var *v);
void	open_semaphores(t_var *v);
void	start_processes(t_var *v);
/*
**		utils1_bonus.c
*/
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
/*
**		utils2_bonus.c
*/
int		msg_bad_arguments(void);
int		errmsg(char *str, int err);
int		ft_atoi(const char *str);

#endif
