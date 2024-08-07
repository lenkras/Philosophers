NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo.c \
		utils_functions.c \
		input_validation.c \
		philo_routine.c \
		monitor.c \
		threads.c \
		philo_eat_routine.c \
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re