NAME = philo

CC = cc

SRC = main.c src/errors/*.c src/parcing/*.c src/tools/*.c src/algo/*.c

all:
	${CC} -g -pthread ${SRC} -o ${NAME}

# clean:
#	rm -f ${NAME}
fclean: #fclean
	rm -f ${NAME}
re: fclean all