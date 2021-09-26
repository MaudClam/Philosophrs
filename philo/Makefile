#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: mclam <mclam@student.21-school.ru>         +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2021/09/25 07:02:55 by mclam             #+#    #+#             *#
#*   Updated: 2021/09/25 07:03:09 by mclam            ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME =		philo

SRCS =		main.c \
			philo.c \
			philo1.c \
			threads.c \
			utils.c \
			utils1.c \
			utils2.c
			
OBJS =		$(SRCS:.c=.o)

HEADER = 	header.h

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror -pthread

# The test flag is taken from the command line, for example:
# make re TEST="-D TIME_DELAY=100"

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) $(TEST) -c $< -o $(<:.c=.o)

all :		$(NAME)
			@echo "Make done"

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(TEST) $(OBJS) -o $(NAME)

clean :
			@rm -f $(OBJS) $(HEADER).gch
			@echo "Make clean done"

fclean 	:	clean
			@rm -f $(NAME)
			@echo "Make fclean done"

re :		fclean all

norm:
			norminette *.c *.h

.PHONY :	all clean fclean re norm
