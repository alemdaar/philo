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

// void *guarding(void *arg)
// {
//     t_info *dainfo = (t_info *) arg;
//     while (1)
//     {
//         if (dainfo->death IS DEAD)
//         {
//             pthread_mutex_lock(&dainfo->write);
//             printf ("%d %d died\n", get_time(dainfo->starting_time), dainfo->);
//             pthread_mutex_unlock(&dainfo->write);
//             return ;
//         }
//     }
    
// }

void *datask(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // pthread_mutex_lock(&philo->dainfo->write);
    // printf("inside : %d\n", philo->id);
    // pthread_mutex_unlock(&philo->dainfo->write);

    if ((philo->id % 2) == 0)
    {
        // pthread_mutex_lock(&philo->dainfo->write);
        // printf ("\033[1;31mndakhl : %d ------------*****\033[0m\n", philo->id);
        // pthread_mutex_unlock(&philo->dainfo->write);
        usleep(50);
    }
    if (philo->id % 2 == 0) // 2 4
    {
        while (1)
        {
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            write (1, ".\n", 2);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d took right fork\n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d took left fork\n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d is eating\n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            usleep(1000000);
            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d leaves left fork\n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d leaves right fork\n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
        }
    }
    else // 1 3 5 
    {
        while (1) 
        {
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d took left fork else \n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d took right fork  else \n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d is eating else \n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            usleep(1000000);

            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);

            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d leaves left fork\n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);

            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d leaves right fork\n", get_time(philo->dainfo->starting_time), philo->id);
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
	started_timimg(dainfo);
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
