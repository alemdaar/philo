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

long long started_timimg(void)
{
    struct timeval current_time;
    if (gettimeofday(&current_time, NULL) == -1)
    {
        output("gettimeofday failed\n", 2);
        return ERROR;
    }
    return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long long get_time(t_info *dainfo)
{
    struct timeval current_time;
    if (gettimeofday(&current_time, NULL) == -1)
        output("gettimeofday failed\n", 2);
    return (started_timimg() - dainfo->starting_time);
}

int holding(t_philo *philo, int duration)
{
    long long now;

    now = get_time(philo->dainfo);
    while ((get_time(philo->dainfo) - now) <= duration)
	{
		pthread_mutex_lock(&philo->dainfo->death_mtx);
		if (philo->dainfo->death IS DEAD)
        {
            // pthread_mutex_lock(&philo->dainfo->write);
            // printf (RED "daz mn hna ++++\n" RESET);
            // pthread_mutex_unlock(&philo->dainfo->write);
			return FAILED;
        }
		pthread_mutex_unlock(&philo->dainfo->death_mtx);
        philo->health += (get_time(philo->dainfo) - philo->last_meal);
        // if (philo->health >= philo->dainfo->time_to_die)
        // {
		//     pthread_mutex_lock(&philo->dainfo->death_mtx);
 		//     philo->dainfo->death = 1;
 		//     philo->dainfo->died_id = philo->id;
		//     pthread_mutex_unlock(&philo->dainfo->death_mtx);
        //     break;
        // }
		usleep(500);
	}
    return SUCCESSFUL;
}

void *guarding(void *arg)
{
    t_info *dainfo = (t_info *) arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < dainfo->number_of_philosophers)
        {
            if (dainfo->philos[i].health >= dainfo->time_to_die)
            {
                pthread_mutex_lock(&dainfo->death_mtx);
                dainfo->death = 1;
                pthread_mutex_lock(&dainfo->write);
                printf (RED "daz mn hna ++++\n" RESET);
                pthread_mutex_unlock(&dainfo->write);
                pthread_mutex_unlock(&dainfo->death_mtx);
                pthread_mutex_lock(&dainfo->write);
                printf (RED "%lld %d died\n" RESET, get_time(dainfo), i + 1);
                printf (RED "because in %lld the id %d had %d health\n" RESET, get_time(dainfo), i + 1, dainfo->philos[i].health);
                
                pthread_mutex_unlock(&dainfo->write);
                return SUCCESSFUL;
            }
            i++;
        }
    }
    
}

int thinking(t_philo *philo)
{
    status(philo, THINK, WHITE);
    return SUCCESSFUL;
}

int sleeping(t_philo *philo)
{
    int r;

    status(philo, SLEEP, MAGENTA);
    r = holding(philo, philo->dainfo->time_to_sleep);
    if (r IS FAILED)
        return FAILED;
    return SUCCESSFUL;
}

int eating(t_philo *philo)
{
    int r;

    pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
    status(philo, FORK, CYAN);

    pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
    status(philo, FORK, CYAN);

    philo->health = 0;
    philo->last_meal = get_time(philo->dainfo);

    status(philo, EAT, GREEN);
    r = holding(philo, philo->dainfo->time_to_eat);
    if (r IS FAILED)
        return FAILED;
    pthread_mutex_lock(&philo->dainfo->write);
    printf (RED "%lld %d is %d\n" RESET, get_time(philo->dainfo), philo->id, philo->health);
    pthread_mutex_unlock(&philo->dainfo->write);

    pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
    pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);

    return SUCCESSFUL;
}

void *datask(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int r;

    if (philo->dainfo->trouble IS ERROR)
        return NULL;

    philo->health = 0;
    philo->last_meal = get_time(philo->dainfo);

    if (philo->id % 2 == 0) // 2 4
    {
        thinking(philo);
        holding(philo, philo->dainfo->time_to_eat / 2);
    }

    while (1)
    {
        r = eating(philo);
        if (r IS FAILED)
            return NULL;
        // long long daba = get_time(philo->dainfo);
        r = sleeping(philo);
        if (r IS FAILED)
            return NULL;
        // long long mora = get_time(philo->dainfo);
        pthread_mutex_lock(&philo->dainfo->write);
        // printf (RED "%lld %d daba %lld\n" RESET, get_time(philo->dainfo), philo->id, daba);
        // printf (RED "%lld %d mora %lld\n" RESET, get_time(philo->dainfo), philo->id, mora);
        // printf (RED "%lld %d natija %lld\n" RESET, get_time(philo->dainfo), philo->id, mora - daba);
        pthread_mutex_unlock(&philo->dainfo->write);

        thinking(philo);
    }
    return NULL;
}

int algo(t_philo *philo, t_info* dainfo)
{
    int r;
	int i;

	i = 0;
	r = pthread_create(&dainfo->gaurd, NULL, guarding, dainfo);
	dainfo->starting_time = started_timimg();
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
    r = pthread_join(dainfo->gaurd, NULL);
    if (r NOT SUCCESSFUL)
    {
    	// free_all();
    	output("Error: waiting thread", 2);
        return ERROR;
    }
	i = 0;
	while (i < dainfo->number_of_philosophers)
    {
		r = pthread_join(philo[i].thread, NULL);
		if (r NOT SUCCESSFUL)
		{
			// free_all();
			output("Error: waiting thread", 2);
            return ERROR;
		}
        i++;
    }
	return SUCCESSFUL;
}
