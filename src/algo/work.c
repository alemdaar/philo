#include "../../header.h"

void run_th(t_info *dainfo)
{
    int r;
    int i;

	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
    	r = pthread_create(dainfo->, NULL, itstime, NULL);
    	if (r != 0) {
    	    fprintf(stderr, "Error creating thread 2\n");
    	    return 1;
    	}
    	printf("Main: Threads created. Waiting for them to finish...\n");
    	r = pthread_join(philo, NULL);
    	if (r != 0) {
    	    fprintf(stderr, "Error creating thread 2\n");
    	    return 1;
    	}
	}
}

int set_forks(t_info *dainfo)
{
    
}

void algo(t_info *dainfo)
{
	int i;

	i = 0;
    while (1)
    {
        set_forks(dainfo);
        run_th(dainfo);
    }
	i++;
	if (i == 2)
		i = 0;
}