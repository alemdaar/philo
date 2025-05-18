#include "../../header.h"

void output(char *str, int fd)
{
	write (fd, str, mystrlen(str));
}

void started_timimg(t_info *dainfo)
{
	struct timeval current_time;
	if (gettimeofday(&current_time, NULL) == -1)
		output("gettimeofday failed\n", 2);
	dainfo->starting_time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return ;
}

suseconds_t get_time(suseconds_t start)
{
	struct timeval current_time;
	if (gettimeofday(&current_time, NULL) == -1)
		output("gettimeofday failed\n", 2);
	suseconds_t tmp = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	tmp -= start;
	return (tmp);
}

void *datask(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_info *dainfo = philo->dainfo;
	printf ("%d %d entered\n", get_time(dainfo->starting_time), philo->id);
	pthread_mutex_lock(&dainfo->forks[(philo->id) - 1]);
	printf ("%d %d has taken a fork\n", get_time(dainfo->starting_time), philo->id);
	printf ("%d %d is eating\n", get_time(dainfo->starting_time), philo->id);
	int long long tmp = 0;
	while (tmp < 5000000000) tmp++;
	// printf ("philo in mutex is %d\n", philo->id);
	printf ("%d %d finished\n", get_time(dainfo->starting_time), philo->id);
	pthread_mutex_unlock(&dainfo->forks[(philo->id) - 1]);
	return NULL;
}

int algo(t_philo *philo, t_info* dainfo)
{
    int r;
	int i;
	t_philo *tmp;

    i = dainfo->pair;
	started_timimg(dainfo);
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
	r = pthread_create(&philo[i].thread, NULL, datask, &philo[i]);
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
}
