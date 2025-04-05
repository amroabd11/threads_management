CC = cc
CFLAGS = -Wall -Wextra -Wall -pthread
NAME = philo
SRC = main.c philo_utils.c errors.c base_functions.c monitoring.c eat_sle_thk.c
OBJ = ${SRC:.c=.o}

all:$(NAME)
$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
%.o:%.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean:clean
	rm -f $(NAME)
re:clean all