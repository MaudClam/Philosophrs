#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2021/09/25 07:05:28 by mclam             #+#    #+#             *#
#*   Updated: 2021/09/25 07:05:28 by mclam            ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME =		philo_bonus

SRCS =		main_bonus.c \
			philo_bonus.c \
			philo1_bonus.c \
			time_bonus.c \
			utils1_bonus.c \
			utils2_bonus.c
			
OBJS =		$(SRCS:.c=.o)

HEADER = 	header_bonus.h

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror -pthread -O3

# The test flag is taken from the command line, for example:
# make re TEST="-D TIME_DELAY=100"

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) $(TEST) -c $< -o $(<:.c=.o)

all :		$(NAME)
			@echo "Make done"

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(TEST) $(OBJS) -o $(NAME)

clean :
			@rm -f $(OBJS)
			@echo "Make clean done"

fclean 	:	clean
			@rm -f $(NAME)
			@echo "Make fclean done"

re :		fclean all

norm:
			norminette

.PHONY :	all clean fclean re norm
