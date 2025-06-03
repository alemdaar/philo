#include "../../header.h"

void output(char *str, int fd)
{
    write (fd, str, mystrlen(str));
}

void	status(t_philo *philo, char *action, long long date)
{
	pthread_mutex_lock(&philo->dainfo->death_mtx);
	if (!philo->dainfo->death)
        printf("%lld %d %s\n", date, philo->id, action);
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
        {
		    pthread_mutex_unlock(&philo->dainfo->death_mtx);
			return FAILED;
        }
		pthread_mutex_unlock(&philo->dainfo->death_mtx);

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
        if (dainfo->philos[i].count_meals == dainfo->number_of_times_each_philosopher_must_eat)
        {
            status(&dainfo->philos[0], "guard khrj", get_time(dainfo));
            return NULL;
        }
        while (i < dainfo->number_of_philosophers)
        {
            pthread_mutex_lock(&dainfo->philos[i].health_mtx);
        	dainfo->philos[i].health = (get_time(dainfo) - dainfo->philos[i].last_meal);
            if (dainfo->philos[i].health >= dainfo->time_to_die)
            {
                pthread_mutex_lock(&dainfo->death_mtx);

                dainfo->death = 1;

                printf ("%lld %d died\n", get_time(dainfo), i + 1);

                pthread_mutex_unlock(&dainfo->death_mtx);
                pthread_mutex_unlock(&dainfo->philos[i].health_mtx);

                return NULL;
            }
            pthread_mutex_unlock(&dainfo->philos[i].health_mtx);
            i++;
        }
    }
    return NULL;
}

int thinking(t_philo *philo, long long date)
{
    status(philo, THINK, date);
    return SUCCESSFUL;
}

int sleeping(t_philo *philo, long long date)
{
    int r;

    status(philo, SLEEP, date);
    holding(philo, philo->dainfo->time_to_sleep);
    return SUCCESSFUL;
}

int eating(t_philo *philo)
{
    int r;
    long long daba;

    pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
    daba = get_time(philo->dainfo);
    status(philo, FORK, daba);

    pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
    daba = get_time(philo->dainfo);
    status(philo, FORK, daba);
	
    pthread_mutex_lock(&philo->health_mtx);
    philo->health = 0;
    pthread_mutex_unlock(&philo->health_mtx);
    philo->last_meal = get_time(philo->dainfo);

    daba = get_time(philo->dainfo);
    status(philo, EAT, daba);
    r = holding(philo, philo->dainfo->time_to_eat);
    if (r IS FAILED)
    {
        pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);
        pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
        return FAILED;
    }
    philo->count_meals += 1;

    pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
    pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);

    return SUCCESSFUL;
}

void *datask(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long long daba;
    int r;
    int i;

    if (philo->dainfo->trouble IS ERROR)
        return NULL;
    philo->last_meal = get_time(philo->dainfo);
    if (philo->id % 2 == 0) // 2 4
    {
        status(philo, THINK, get_time(philo->dainfo));
        holding(philo, philo->dainfo->time_to_eat / 2);
    }
    if (philo->dainfo->nb_of_inputs == 4)
    {
        while (1)
        {
        	r = eating(philo);
        	if (r IS FAILED)
        	    return NULL;
            daba = get_time(philo->dainfo);
        	sleeping(philo, daba);
            daba = get_time(philo->dainfo);
        	thinking(philo, daba);
        }
    }
	else
	{
		i = 0;
        while (i < philo->dainfo->number_of_times_each_philosopher_must_eat)
        {
        	r = eating(philo);
        	if (r IS FAILED)
        	{
        	    pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
        	    pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);
        	    return NULL;
        	}
            daba = get_time(philo->dainfo);
        	sleeping(philo, daba);
            daba = get_time(philo->dainfo);
        	thinking(philo, daba);
			i++;
        }
	}
    return NULL;
}

void *onephilo_task(void *arg)
{
    t_philo *philo = (t_philo *)arg;
	philo->dainfo->starting_time = started_timimg();
    printf("%lld %d %s\n", get_time(philo->dainfo), philo->id, FORK);
    holding(philo, philo->dainfo->time_to_die);
    printf("%lld %d %s\n", get_time(philo->dainfo), philo->id, DYING);
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
        free_all(dainfo)
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
		if (r NOT SUCCESSFUL)
		{
            // free_all
			output("Error: waiting thread", 2);
            return ERROR;
		}
        i++;
    }
	return SUCCESSFUL;
}
