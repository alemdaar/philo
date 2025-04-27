NAME = philo

CC = cc

SRC = main.c src/errors/*.c src/parcing/*.c src/tools/*.c

all:
	${CC} -g -pthread ${SRC} -o ${NAME}