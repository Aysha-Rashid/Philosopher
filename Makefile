NAME = Philo

SCR= main.c \
	utils.c

OBJ = $(SCR:.c=.o)

$NAME: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean $(NAME)