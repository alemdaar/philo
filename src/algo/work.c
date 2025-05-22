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
    dainfo->starting_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
}

suseconds_t get_time(suseconds_t start)
{
    struct timeval current_time;
    if (gettimeofday(&current_time, NULL) == -1)
        output("gettimeofday failed\n", 2);
    suseconds_t current_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
    return (current_ms - start);
}

void *guarding(void *arg)
{
    t_info *dainfo = (t_info *) arg;
    while (1)
    {
        if (dainfo->death IS DEAD)
        {
            pthread_mutex_lock(&dainfo->write);
            printf ("%d %d died\n", get_time(dainfo->starting_time), dainfo->);
            pthread_mutex_unlock(&dainfo->write);
            return ;
        }
    }
    
}

void *datask(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_info *dainfo = philo->dainfo;
    printf ("inside : %d ------------\n", philo->id);
    while (1) {
        // Lock forks in order (prevent deadlock)
        if ()
        usleep(200); // Simulate eating
        pthread_mutex_lock(&dainfo->forks[philo->fork[RIGHT]]);
    
        pthread_mutex_lock(&dainfo->write);
        printf("%d %d took left fork\n", get_time(dainfo->starting_time), philo->id);
        pthread_mutex_unlock(&dainfo->write);

        pthread_mutex_lock(&dainfo->forks[philo->fork[LEFT]]);
    
        pthread_mutex_lock(&dainfo->write);
        printf("%d %d took right fork\n", get_time(dainfo->starting_time), philo->id);
        printf("%d %d is eating\n", get_time(dainfo->starting_time), philo->id);
        pthread_mutex_unlock(&dainfo->write);


        pthread_mutex_unlock(&dainfo->forks[philo->fork[LEFT]]);
        pthread_mutex_unlock(&dainfo->forks[philo->fork[RIGHT]]);

        // Optional: Add thinking/sleeping logic
    }
    return NULL;
}

int algo(t_philo *philo, t_info* dainfo)
{
    int r;
	int i;

	i = 0;
	r = pthread_create(&philo[i].thread, NULL, guarding, &philo[i]);
    i = 0;
	started_timimg(dainfo);
    while (i < dainfo->number_of_philosophers)
    {
		printf ("see it ++++++++++ %d\n", philo[i].id);
		r = pthread_create(&philo[i].thread, NULL, datask, &philo[i]);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			why_exit("Error creating thread\n", 1);
		}
        i ++;
    }
	while (i < dainfo->number_of_philosophers)
    {
		r = pthread_join(philo[i].thread, NULL);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			why_exit("Error: waiting thread", 1);
		}
        i ++;
    }
	exit(0);
	return SUCCESSFUL;
}
