CC = cc

NAME = philo

CFLAGS = -Wall -Wextra -Werror -g -pthread

SRC = main.c src/algo/time.c src/algo/work.c src/algo/work2.c src/algo/work3.c \
	src/tools/tools.c src/parcing/parcing.c src/free/free.c src/init/init.c src/init/mutex.c

OBJ = ${SRC:.c=.o}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


all: ${NAME}

$(NAME): $(OBJ)
	@$(CC) $(OBJ) ${CFLAGS} -o $(NAME)
	@echo "compiled successfully !"

clean :
	@rm -f ${OBJ}
	@echo "cleaned successfully !"

fclean : clean
	@rm -f ${NAME}
re : fclean all
