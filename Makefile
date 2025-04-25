NAME = philo

CC = cc

SRC = main.c src/errors/*.c



all:
	${CC} -g -pthread ${SRC} -o ${NAME}