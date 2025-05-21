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

void *datask(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_info *dainfo = philo->dainfo;
    int left_fork = philo->id - 1;
    int right_fork = philo->id % dainfo->number_of_philosophers;

    while (1) {
        // Lock forks in order (prevent deadlock)
        pthread_mutex_lock(&dainfo->forks[left_fork]);
        pthread_mutex_lock(&dainfo->write);
        printf("%d %d took left fork\n", get_time(dainfo->starting_time), philo->id);
        pthread_mutex_unlock(&dainfo->write);

        pthread_mutex_lock(&dainfo->forks[right_fork]);
        pthread_mutex_lock(&dainfo->write);
        printf("%d %d took right fork\n", get_time(dainfo->starting_time), philo->id);
        printf("%d %d is eating\n", get_time(dainfo->starting_time), philo->id);
        pthread_mutex_unlock(&dainfo->write);

        usleep(dainfo->time_to_eat * 1000); // Simulate eating

        pthread_mutex_unlock(&dainfo->forks[left_fork]);
        pthread_mutex_unlock(&dainfo->forks[right_fork]);

        // Optional: Add thinking/sleeping logic
    }
    return NULL;
}

int algo(t_philo *philo, t_info* dainfo)
{
    int r;
	int i;

	started_timimg(dainfo);
	i = 0;
    while (i < dainfo->number_of_philosophers)
    {
		printf ("see it %d\n", philo[i].id);
		r = pthread_create(&philo[i].thread, NULL, datask, &philo[i]);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			why_exit("Error creating thread\n", 1);
		}
        i ++;
    }
	r = pthread_create(&philo[i].thread, NULL, datask, &philo[i]);
    i = 0;
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
