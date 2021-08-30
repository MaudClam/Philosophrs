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

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all :		$(NAME)
			@echo "Make done"

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean :
			rm -f $(OBJS)

fclean 	:	clean
			rm -f $(NAME)

re :		fclean all

norm:
			norminette *.c *.h

.PHONY :	all clean fclean re norm
