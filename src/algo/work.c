#include "../../header.h"

void output(char *str, int fd)
{
    write (fd, str, mystrlen(str));
}

void	status(t_philo *philo, char *action, char *color)
{
	pthread_mutex_lock(&philo->dainfo->death_mtx);
	if (!philo->dainfo->death)
	{
		pthread_mutex_lock(&philo->dainfo->write);
        printf("%s", color);
        printf("%lld %d %s\n" RESET, get_time(philo->dainfo), philo->id, action);
		pthread_mutex_unlock(&philo->dainfo->write);
	}
	pthread_mutex_unlock(&philo->dainfo->death_mtx);
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

int holding(t_philo *philo, int duration)
{
    int r;
    long long now;

    now = get_time(philo->dainfo);
    // pthread_mutex_lock(&philo->dainfo->write);
	// pthread_mutex_unlock(&philo->dainfo->write);
    while ((get_time(philo->dainfo)) - now < philo->dainfo->time_to_eat)
	{
        // write (1, "-\n", 2);
		pthread_mutex_lock(&philo->dainfo->death_mtx);
		r = philo->dainfo->death;
		pthread_mutex_unlock(&philo->dainfo->death_mtx);
		if (r IS DEAD)
			break ;
		usleep(500);
	}
    return SUCCESSFUL;
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

static int thinking(t_philo *philo)
{
    status(philo, THINK, WHITE);
    return SUCCESSFUL;
}

static int sleeping(t_philo *philo)
{
    status(philo, SLEEP, MAGENTA);
    holding(philo, philo->dainfo->time_to_sleep);
    return SUCCESSFUL;
}
static int eating(t_philo *philo)
{
    status(philo, EAT, GREEN);
    holding(philo, philo->dainfo->time_to_eat);
    return SUCCESSFUL;
}

void *datask(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    if (philo->dainfo->trouble IS ERROR)
        return NULL;
    if (philo->id % 2 == 0) // 2 4
    {
        thinking(philo);
        holding(philo, philo->dainfo->time_to_eat / 2);
        while (1)
        {
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            // status(philo, FORK, CYAN);
            pthread_mutex_lock(&philo->dainfo->write);
            printf(CYAN "%lld %d has taken %d fork\n" RESET, get_time(philo->dainfo), philo->id, philo->fork[RIGHT]);
		    pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
            // status(philo, FORK, CYAN);
            pthread_mutex_lock(&philo->dainfo->write);
            printf(CYAN "%lld %d has taken %d fork\n" RESET, get_time(philo->dainfo), philo->id, philo->fork[LEFT]);
		    pthread_mutex_unlock(&philo->dainfo->write);
            eating(philo);
            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf(RED "%lld %d leaves the %d fork\n" RESET, get_time(philo->dainfo), philo->id, philo->fork[LEFT]);
		    pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf(RED "%lld %d leaves the %d fork\n" RESET, get_time(philo->dainfo), philo->id, philo->fork[RIGHT]);
		    pthread_mutex_unlock(&philo->dainfo->write);
            sleeping(philo);
            thinking(philo);
            // return NULL;
        }
    }
    else 
    {
        while (1)
        {
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
            // status(philo, FORK, CYAN);
            pthread_mutex_lock(&philo->dainfo->write);
            printf(CYAN "%lld %d has taken %d fork\n" RESET, get_time(philo->dainfo), philo->id, philo->fork[LEFT]);
		    pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            // status(philo, FORK, CYAN);
            pthread_mutex_lock(&philo->dainfo->write);
            printf(CYAN "%lld %d has taken %d fork\n" RESET, get_time(philo->dainfo), philo->id, philo->fork[RIGHT]);
		    pthread_mutex_unlock(&philo->dainfo->write);
            // pthread_mutex_lock(&philo->dainfo->write);
            // write (1, "*\n", 2);
            // // printf(RED "%lld %d %s\n" RESET, get_time(philo->dainfo), philo->id, "TEST2");
		    // pthread_mutex_unlock(&philo->dainfo->write);
            eating(philo);
            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf(RED "%lld %d leaves the %d fork\n" RESET, get_time(philo->dainfo), philo->id, philo->fork[RIGHT]);
		    pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf(RED "%lld %d leaves the %d fork\n" RESET, get_time(philo->dainfo), philo->id, philo->fork[LEFT]);
		    pthread_mutex_unlock(&philo->dainfo->write);
            sleeping(philo);
            thinking(philo);
            // return NULL;
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
		r = pthread_create(&philo[i].thread, NULL, datask, &philo[i]);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			output("Error creating thread\n", 2);
            dainfo->trouble = -1;
            return ERROR;
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
			output("Error: waiting thread", 2);
            dainfo->trouble = -1;
            return ERROR;
		}
        i++;
    }
	return SUCCESSFUL;
}
