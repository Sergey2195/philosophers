NAME = philo

HEADER	=	philo.h

SRC	=	before_end.c error.c ft_atoi.c init.c living.c main.c utils.c living2.c

CC 		= gcc

FLAGS	= -Wall -Wextra -Werror

LINKS	=	-lpthread

OBJS 	= $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(LINKS) $(SRC) -o $(NAME)

all: $(NAME) $(OBJS) $(HEADER)

%.o: %.c $(HEADER)
		$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re