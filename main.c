#include "header.h"

void free_all(t_info *dainfo)
{
	free(dainfo->forks);
	free(dainfo->philos);
	return ;
}

void clean(t_info *dainfo)
{
	int	i;
	i = 0;
    while (i < dainfo->number_of_philosophers)
    {
		pthread_mutex_destroy(&dainfo->philos[i].health_mtx);
		pthread_mutex_destroy(&dainfo->forks[i]);
		i++;
    }
	pthread_mutex_destroy(&dainfo->death_mtx);
    free_all(dainfo);
	return ;
}

int main (int ac, char **av)
{
    t_info	dainfo;
    t_philo	*philo;
    int		r;

    if(ac NOT 5 && ac NOT 6) 
        return(output("number of args is not valid\n", 2), 1);
    r = parcing(ac, av, &dainfo);
    if (r IS FAILED)
        return (1);
    r = init(ac, av, &dainfo, &philo);
    if (r IS FAILED)
        return (1);
    if (dainfo.number_of_philosophers == 1)
        r = one_philo(philo, &dainfo);
    else
        r = algo(philo, &dainfo);
    if (r IS ERROR)
        return (1);
    clean(&dainfo);
	return 0;
}
