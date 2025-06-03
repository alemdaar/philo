#ifndef HEADER_H
#define HEADER_H

// headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

// macros

#define FORK "has taken a fork"
#define EAT "is eating"
#define THINK "is thinking"
#define SLEEP "is sleeping"
#define DYING "died"

// =========
#define TAKEN 1
#define SINGLE 0
#define TRUE 1
#define FALSE 0
#define SUCCESSFUL 0
#define FAILED 1
#define ERROR -1
#define LEFT 1
#define RIGHT 0
#define PAIR 0
#define UNPAIR 1
#define STDOUT 1
#define STDERR 2
#define NOT !=
#define IS ==
#define OR ||
#define DEAD 1

// struct
typedef struct s_info t_info;
typedef struct s_philo
{
    int id;
    pthread_t thread;
    int count_meals;
    int fork[2];
    long long last_meal;
    int health;
    pthread_mutex_t health_mtx;
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
    int death;
    int died_id;
    int trouble;
    long long starting_time;
    pthread_mutex_t *forks;
    pthread_t gaurd;
    pthread_mutex_t write;
    pthread_mutex_t death_mtx;
    t_philo *philos;
    long long int tmp_nb[5];
} t_info;



// prototypes
// errors
// parcing
int is_number(char *str);
int set_info(t_info *dainfo, t_philo **philo);
void    check_input(int ac, char **av, t_info *dainfo);
int set_philos(t_info *dainfo, t_philo **philo);
int     parcing(int ac, char **av, t_info *dainfo);
int init(int ac, char **av, t_info *dainfo, t_philo **philo);
int    set_mutex(t_info *dainfo);
// tools
int mystrlen(char *str);
int long long myatoi(char *str);
int holding(t_philo *philo, int duration);
int algo(t_philo *philo, t_info* dainfo);
void *datask(void *arg);
void output(char *str, int fd);
void	status(t_philo *philo, char *action, long long date);
long long started_timimg(void);
long long get_time(t_info *dainfo);
int thinking(t_philo *philo, long long date);
int sleeping(t_philo *philo, long long date);
int eating(t_philo *philo);
int one_philo(t_philo *philo, t_info *dainfo);
void *onephilo_task(void *arg);

#endif