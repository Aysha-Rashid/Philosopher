NAME = philo

SCR= main.c \
	utils.c	\
	extra.c	\
	arguments.c	\

OBJ = $(SCR:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re