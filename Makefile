CC = cc
CFLAGS = -Wall -Wextra -Wall
NAME = philo
SRC = main.c philo_utils.c
OBJ = ${SRC:.c=.o}

all:$(NAME)
$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
%.o:%.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
flcean:clean
	rm -f $(NAME)