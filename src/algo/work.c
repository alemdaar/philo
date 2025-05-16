#include "../../header.h"

void output(char *str, int fd)
{
	write (fd, str, mystrlen(str));
}

void pair_condition(t_info *dainfo)
{
	if (dainfo->pair == PAIR)
		dainfo->pair = UNPAIR;
	else
		dainfo->pair = PAIR;
    return ;
}

void *datask(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_info *dainfo = philo->dainfo;
	pthread_mutex_lock(&dainfo->forks[(philo->id) - 1]);
	printf ("philo in mutex is %d\n", philo->id);
	pthread_mutex_unlock(&dainfo->forks[(philo->id) - 1]);
	return NULL;
}

int prepare_philos(t_philo *philo, t_info* dainfo)
{
    int r;
	int i;
	t_philo *tmp;

    i = dainfo->pair;
    while (i < dainfo->number_of_philosophers)
    {
		printf ("see it %d\n", philo[i].id);
		r = pthread_create(&philo[i].thread, NULL, datask, &philo[i]);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			why_exit("Error creating thread\n", 1);
		}
        i += 2;
    }
    i = dainfo->pair;
	while (i < dainfo->number_of_philosophers)
    {
		r = pthread_join(philo[i].thread, NULL);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			why_exit("Error: waiting thread", 1);
		}
        i += 2;
    }
	return SUCCESSFUL;
}

void algo(t_info *dainfo, t_philo *philo)
{
	// struct timeval current_time;
	// gettimeofday(&current_time, NULL);
	while (1)
	{
        prepare_philos(philo, dainfo);
    	pair_condition(dainfo);
	}
}
