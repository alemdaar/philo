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
    while ((get_time(philo->dainfo) - now) < duration)
	{
		pthread_mutex_lock(&philo->dainfo->death_mtx);
		if (philo->dainfo->death IS DEAD)
			return FAILED;
		pthread_mutex_unlock(&philo->dainfo->death_mtx);
		usleep(1);
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
            pthread_mutex_lock(&dainfo->meals_mutex);
            if (dainfo->philos[i].count_meals == dainfo->philos[i].dainfo->number_of_times_each_philosopher_must_eat)
            {
                dainfo->meals_reached += 1;
                if (dainfo->meals_reached == dainfo->philos[i].dainfo->number_of_philosophers)
                {
            		pthread_mutex_unlock(&dainfo->meals_mutex);
                    return NULL;
                }
            }
            pthread_mutex_unlock(&dainfo->meals_mutex);
            if (dainfo->philos[i].health > dainfo->time_to_die)
            {
                pthread_mutex_lock(&dainfo->death_mtx);

                dainfo->death = 1;

                pthread_mutex_lock(&dainfo->write);
                printf (RED "%lld %d died\n" RESET, get_time(dainfo), i + 1);
                // printf (RED "bc in %lld the id %d had %d health\n" RESET, get_time(dainfo), i + 1, dainfo->philos[i].health);
                pthread_mutex_unlock(&dainfo->write);

                pthread_mutex_unlock(&dainfo->death_mtx);

                return NULL;
            }
			pthread_mutex_lock(&dainfo->health_mtx);
        	dainfo->philos[i].health = (get_time(dainfo) - dainfo->philos[i].last_meal);
			pthread_mutex_unlock(&dainfo->health_mtx);
            i++;
        }
    }
    return NULL;
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
	
    pthread_mutex_lock(&philo->dainfo->health_mtx);
    philo->health = 0;
    pthread_mutex_unlock(&philo->dainfo->health_mtx);
    philo->last_meal = get_time(philo->dainfo);

    status(philo, EAT, GREEN);
    r = holding(philo, philo->dainfo->time_to_eat);
    if (r IS FAILED)
        return FAILED;
    pthread_mutex_lock(&philo->dainfo->meals_mutex);
    philo->count_meals += 1;
    pthread_mutex_unlock(&philo->dainfo->meals_mutex);
    // pthread_mutex_lock(&philo->dainfo->write);
    // printf (RED "%lld %d hna\n" RESET, get_time(philo->dainfo), philo->id);
    // pthread_mutex_unlock(&philo->dainfo->write);
    // pthread_mutex_lock(&philo->dainfo->write);
    // printf (RED "%lld %d is %d\n" RESET, get_time(philo->dainfo), philo->id, philo->health);
    // pthread_mutex_unlock(&philo->dainfo->write);

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
        if (philo->count_meals == philo->dainfo->number_of_times_each_philosopher_must_eat)
            return NULL;
        r = sleeping(philo);
        if (r IS FAILED)
            return NULL;
        pthread_mutex_lock(&philo->dainfo->write);
        pthread_mutex_unlock(&philo->dainfo->write);

        thinking(philo);
    }
    return NULL;
}

void *onephilo_task(void *arg)
{
    t_philo *philo = (t_philo *)arg;
	philo->dainfo->starting_time = started_timimg();
    printf(CYAN "%lld %d %s\n" RESET, get_time(philo->dainfo), philo->id, FORK);
    holding(philo, philo->dainfo->time_to_die);
    printf(RED "%lld %d %s\n" RESET, get_time(philo->dainfo), philo->id, DYING);
    return NULL;
}

int one_philo(t_philo *philo, t_info *dainfo)
{
    int r;
	int i;

	i = 0;
	r = pthread_create(&philo->thread, NULL, onephilo_task, philo);
	if (r NOT SUCCESSFUL)
	{
		// free_all();
		output("Error creating thread\n", 2);
        dainfo->trouble = -1;
        return ERROR;
	}
	r = pthread_join(philo->thread, NULL);
	if (r NOT SUCCESSFUL)
	{
		// free_all();
		output("Error: waiting thread", 2);
        return ERROR;
	}
    // pthread_mutex_lock(&philo->dainfo->write);
    // printf (GREEN "%lld came here\n" RESET, get_time(philo->dainfo));
    // pthread_mutex_unlock(&philo->dainfo->write);
	return SUCCESSFUL;
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
        // pthread_mutex_lock(&philo->dainfo->write);
        // printf (GREEN "%lld wsal hna\n" RESET, get_time(philo->dainfo));
        // pthread_mutex_unlock(&philo->dainfo->write);
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
