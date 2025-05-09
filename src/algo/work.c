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
	write ("datask\n");
	// t_philo *tmp = (t_philo *)arg;
	t_info *tmp = (t_info *)arg;
	t_philo *see = tmp->current_philo;
	printf ("philo beofre mutex is %d-----\n", see->id);
	printf ("number is %d-----\n", (see->id) - 1);
	pthread_mutex_lock(&tmp->forks[(see->id) - 1]);
	// while (1);
	int long long num = 0;
	while (num < 1000000000)
		num ++;
	printf ("philo in mutex is %d\n", see->id);
	pthread_mutex_unlock(&tmp->forks[(see->id) - 1]);
	printf ("khrj---\n");
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
		write(1, ".\n", 2);
		dainfo->current_philo = &dainfo->philos[i];
		tmp = dainfo->current_philo;
		printf ("tmp id %d\n", tmp->id);
		r = pthread_create(&tmp->thread, NULL, datask, dainfo);
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
	write (1, "done\n", 5);
	exit(0);
	return SUCCESSFUL;
}
void algo(t_info *dainfo, t_philo *philo)
{
	while (1)
	{
        prepare_philos(philo, dainfo);
    	pair_condition(dainfo);
	}
}