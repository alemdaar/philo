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
	printf ("dkhal---\n");
	t_info *dainfo;
	dainfo = (t_info *)arg;
	t_philo *tmp = dainfo->current_philo;
	printf ("philo is %d-----\n", tmp->id);
	pthread_mutex_lock(&dainfo->lock);
	printf ("philo is %d\n", tmp->id);
	pthread_mutex_unlock(&dainfo->lock);
	// pthread_mutex_unlock
	printf ("khrj---\n");
	return NULL;
}
int make_thread(t_info* dainfo)
{
	int r;
	t_philo *tmp = dainfo->current_philo;
	printf ("nshufu philo : %d\n", tmp->id);
    r = pthread_create(&tmp->thread, NULL, datask, dainfo);
    if (r NOT SUCCESSFUL)
	{
		// free_all();
        why_exit("Error creating thread 2\n", 1);
    }
	return SUCCESSFUL;
}

int wait_thread(t_info *dainfo)
{
	int r;
	t_philo *tmp;

	tmp = dainfo->current_philo;
	r = pthread_join(tmp->thread, NULL);
	if (r != SUCCESSFUL)
	{
		// free_all();
	    why_exit("Error: waiting thread", 1);
	}
	return SUCCESSFUL;
}
int prepare_philos(t_philo *philo, t_info* dainfo)
{
    int r;
	int i;
	t_philo *tmp;

    i = dainfo->pair;
	// printf ("dainfo pair : %d\n", dainfo->pair);
    while (i <= dainfo->number_of_philosophers)
    {
		tmp = &dainfo->philos[i];
		dainfo->current_philo = &dainfo->philos[i];
		// printf ("loop 1, i = %d\n", i);
		// printf ("tmp id %d\n", tmp->id);
		make_thread(dainfo);
        i += 2;
    }
    i = dainfo->pair;
	while (i <= dainfo->number_of_philosophers)
    {
		// printf ("loop 2, i = %d\n", i);
		dainfo->current_philo = &dainfo->philos[i];
        wait_thread(dainfo);
        i += 2;
    }
	exit(0);
	return SUCCESSFUL;
    // π
}
void algo(t_info *dainfo, t_philo *philo)
{
	while (1)
	{
        prepare_philos(philo, dainfo);
    	pair_condition(dainfo);
	}
}