/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:28:39 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/14 22:36:28 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>


// macros

# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DYING "died"

# define ERR_CSP "Error: creating semaphore\n"
# define ERR_CTH "Error: creating semaphore\n"
# define ERR_JTH "Error: joining thread\n"
# define ERR_ISP "Failed to initialize semaphore.\n"
# define ERR_MAF "Memory allocation failed.\n"
# define ERR_NNB "!= a number\n"
# define ERR_NGT "Negative number in the input\n"
# define ERR_NB0 "one of the inputs is 0\n"

// =========
# define SUCCESSFUL 0
# define FAILED 1
# define ERROR -1
# define LEFT 1
# define RIGHT 0
# define DEAD 1

// struct
typedef struct s_info	t_info;

typedef struct s_philo
{
	int				id; //
	pid_t           pid; //------
	pthread_t		thread; //-----
	int				fork[2]; //
	long long		last_meal; //
	int				health; //
	int				count_meal; //
	sem_t			*health_smp; //
	sem_t			*meal_smp; //
	sem_t			*count_smp; //
	t_info			*dainfo; //
}	t_philo;

typedef struct s_info
{
	int				number_of_philosophers; //
	int				time_to_die; //
	int				time_to_eat; //
	int				time_to_sleep;//
	int				number_of_times_each_philosopher_must_eat; //
	int				nb_of_inputs; //
	long long		starting_time; //----------
	pthread_t		guard; //----------
	sem_t			*forks; //
	sem_t			*write; //
	t_philo			*philos; //
	long long		tmp_nb[5]; //
}	t_info;

int			parcing(int ac, char **av, t_info *dainfo);
int			init(t_info *dainfo, t_philo **philo);
int			semaphores(t_info *dainfo);
int			mystrlen(char *str);
long long	myatoi(char *str);
int			algo(t_info *dainfo);
void		output(char *str, int fd);
void		status(t_philo *philo, char *action, long long date);
long long	started_timimg(void);
long long	get_time(t_info *dainfo);
int			holding(t_philo *philo, int duration);
int			thinking(t_philo *philo, long long date);
int			sleeping(t_philo *philo, long long date);
int			eating(t_philo *philo);
int			one_philo(t_philo *philo, t_info *dainfo);
void		free_all(t_info *dainfo);
void		clean(t_info *dainfo);
void		clean_smp(t_info *dainfo);
int			guarding2(t_philo *philo);
int			limited(t_philo *philo);
int			endless(t_philo *philo);
int			algo2(t_info *dainfo);
char		*ft_itoa(int n);
// int			smp_name(char **str, int i, int len);

#endif