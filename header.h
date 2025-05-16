#ifndef HEADER_H
#define HEADER_H

// headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

// macros
#define TAKEN 1
#define SINGLE 0
#define TRUE 1
#define FALSE 0
#define SUCCESSFUL 0
#define FAILED 1
#define LEFT 1
#define RIGHT 0
#define PAIR 0
#define UNPAIR 1
#define STDOUT 1
#define STDERR 2
#define NOT !=
#define IS ==
#define OR ||

// struct
typedef struct s_info t_info;
typedef struct s_philo
{
    int id;
    pthread_t thread;
    pthread_t lock;
    int count_meals;
    int fork[2];
    t_info *dainfo;
}   t_philo;

typedef struct s_info
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int nb_of_inputs;
    int pair;
    pthread_mutex_t *forks;
    // pthread_mutex_t lock;
    t_philo *philos;
    long long int tmp_nb[5];
} t_info;



// prototypes
// errors
void why_exit(char *str, int status);
// parcing
int is_number(char *str);
int set_info(t_info *dainfo, t_philo **philo);
void    check_input(int ac, char **av, t_info *dainfo);
void set_philos(t_info *dainfo, t_philo **philo);
void    parcing(int ac, char **av, t_info *dainfo);
void	init(int ac, char **av, t_info *dainfo, t_philo **philo);
void    set_mutex(t_info *dainfo);
// tools
int mystrlen(char *str);
int long long myatoi(char *str);
void algo(t_info *dainfo, t_philo *philo);
int prepare_philos(t_philo *philo, t_info* dainfo);
void *datask(void *arg);
void pair_condition(t_info *dainfo);
void output(char *str, int fd);

#endif