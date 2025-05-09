#include "../../header.h"

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

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
	printf ("datask\n");
	// t_philo *tmp = (t_philo *)arg;
	t_info *tmp = (t_info *)arg;
	t_philo *see = tmp->current_philo;
	printf ("philo qbl mutex is %d-----\n", see->id);
	pthread_mutex_lock(&mtx);
	// while (1);
	int long long num = 0;
	while (num < 1000000000)
		num ++;
	printf ("philo fwst is %d\n", see->id);
	pthread_mutex_unlock(&mtx);
	// pthread_mutex_unlock
	printf ("khrj---\n");
	return NULL;
}
// int make_thread(t_info* dainfo)
// {
// }

int prepare_philos(t_philo *philo, t_info* dainfo)
{
    int r;
	int i;
	t_philo *tmp;

    i = dainfo->pair;
	// printf ("dainfo pair : %d\n", dainfo->pair);
    while (i < dainfo->number_of_philosophers)
    {
		write(1, ".\n", 2);
		dainfo->current_philo = &dainfo->philos[i];
		tmp = dainfo->current_philo;
		// printf ("loop 1, i = %d\n", i);
		printf ("tmp id %d\n", tmp->id);
		// make_thread(dainfo);
		// t_philo *tmp = dainfo->current_philo;
		// printf ("nshufu philo : %d\n", tmp->id);
		r = pthread_create(&tmp->thread, NULL, datask, dainfo);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			why_exit("Error creating thread\n", 1);
		}
		return SUCCESSFUL;
        i += 2;
    }
    i = dainfo->pair;
	while (i < dainfo->number_of_philosophers)
    {
		// printf ("loop 2, i = %d\n", i);
		dainfo->current_philo = &dainfo->philos[i];
		tmp = dainfo->current_philo;
		r = pthread_join(tmp->thread, NULL);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			why_exit("Error: waiting thread", 1);
		}
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