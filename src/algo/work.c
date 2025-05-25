#include "../../header.h"

void output(char *str, int fd)
{
	write (fd, str, mystrlen(str));
}

long long started_timimg(t_info *dainfo)
{
    struct timeval current_time;
    if (gettimeofday(&current_time, NULL) == -1)
        output("gettimeofday failed\n", 2);
    return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long long get_time(t_info *dainfo)
{
    struct timeval current_time;
    if (gettimeofday(&current_time, NULL) == -1)
        output("gettimeofday failed\n", 2);
    return (started_timimg(dainfo) - dainfo->starting_time);
}

// void *guarding(void *arg)
// {
//     t_info *dainfo = (t_info *) arg;
//     while (1)
//     {
//         if (dainfo->death IS DEAD)
//         {
//             pthread_mutex_lock(&dainfo->write);
//             printf ("%d %d died\n", get_time(dainfo), dainfo->);
//             pthread_mutex_unlock(&dainfo->write);
//             return ;
//         }
//     }
    
// }

void *datask(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    if (philo->id % 2 == 0) // 2 4
    {
        usleep(100);
        while (1)
        {
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d took right fork -> %d\n", get_time(philo->dainfo), philo->id, philo->fork[RIGHT]);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d took left fork -> %d\n", get_time(philo->dainfo), philo->id, philo->fork[LEFT]);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d is eating\n", get_time(philo->dainfo), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            usleep(500);
            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d leaves left fork -> %d\n", get_time(philo->dainfo), philo->id, philo->fork[LEFT]);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d leaves right fork -> %d\n", get_time(philo->dainfo), philo->id, philo->fork[RIGHT]);
            pthread_mutex_unlock(&philo->dainfo->write);

            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d slept\n", get_time(philo->dainfo), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            usleep(200);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d thinking\n", get_time(philo->dainfo), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
        }
    }
    else 
    {
        while (1) 
        {
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d took left fork else -> %d\n", get_time(philo->dainfo), philo->id, philo->fork[LEFT]);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d took right fork else -> %d\n", get_time(philo->dainfo), philo->id, philo->fork[RIGHT]);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d is eating else \n", get_time(philo->dainfo), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            usleep(500);

            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);

            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d leaves right fork else -> %d\n", get_time(philo->dainfo), philo->id, philo->fork[RIGHT]);
            pthread_mutex_unlock(&philo->dainfo->write);

            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);

            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d leaves left fork else -> %d\n", get_time(philo->dainfo), philo->id, philo->fork[LEFT]);
            pthread_mutex_unlock(&philo->dainfo->write);

            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d slept\n", get_time(philo->dainfo), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            usleep(200);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%lld %d thinking\n", get_time(philo->dainfo), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
        }
    }
    return NULL;
}

int algo(t_philo *philo, t_info* dainfo)
{
    int r;
	int i;

	i = 0;
	// r = pthread_create(&philo[i].thread, NULL, guarding, &philo[i]);
    // i = 0;
	dainfo->starting_time = started_timimg(dainfo);
    while (i < dainfo->number_of_philosophers)
    {
		// printf ("\033[1;34msee it ++++++++++ %d \033[0m\n", philo[i].id);
		r = pthread_create(&philo[i].thread, NULL, datask, &philo[i]);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			why_exit("Error creating thread\n", 1);
		}
        i++;
    }
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
    printf ("END\n");
	// exit(0);
	return SUCCESSFUL;
}
