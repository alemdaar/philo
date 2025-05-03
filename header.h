#ifndef HEADER_H
#define HEADER_H

// headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// macros
#define TAKEN 1;
#define SINGLE 0;
#define TRUE 1;
#define FALSE 0;
#define SUCCESSFUL 0;
#define FAILED 1;

// structs
typedef struct s_philo
{
    int id;
    pthread_t thread;
    pthread_mutex_t mutex;
    ;
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
    int *fork;
    t_philo *philos;
} t_info;



// prototypes
// errors
void why_exit(char *str, int status);
// parcing
int is_number(char *str);
void set_info(t_info *dainfo, long long int nb[5]);
void    check_input(int ac, char **av, t_info *dainfo);
void set_philos(t_info *dainfo, t_philo *philo);
void	parcing(int ac, char **av, t_info *dainfo, t_philo *philo);
// tools
int mystrlen(char *str);
int long long myatoi(char *str);

#endif