#include "../../header.h"

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
