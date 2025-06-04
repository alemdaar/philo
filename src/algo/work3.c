// #include "../../header.h"

int guarding2()
{
    int i;

	i = 0;
	if (dainfo->philos[i].count_meals == must_eat)
		return (NULL);
	while (i < dainfo->number_of_philosophers)
	{
		pthread_mutex_lock(&dainfo->philos[i].health_mtx);
		health = (get_time(dainfo) - dainfo->philos[i].last_meal);
		dainfo->philos[i].health = health;
		if (dainfo->philos[i].health >= dainfo->time_to_die)
		{
			pthread_mutex_lock(&dainfo->death_mtx);
			dainfo->death = 1;
			printf ("%lld %d died\n", get_time(dainfo), i + 1);
			pthread_mutex_unlock(&dainfo->death_mtx);
			pthread_mutex_unlock(&dainfo->philos[i].health_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&dainfo->philos[i++].health_mtx);
	}
}