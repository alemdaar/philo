#include "header.h"

int main (int ac, char **av)
{
    // // number_of_philosophers time_to_die time_to_eat time_to_sleep
    // // [number_of_times_each_philosopher_must_eat] (optional)
    t_info dainfo;
    t_philo philo;
    if (ac != 5 && ac != 6)
        why_exit("number of args is not valid\n", 0);
    parcing(ac, av, &dainfo, &philo);
    printf ("philos : %d\n", dainfo.number_of_philosophers);
    printf ("die : %d\n", dainfo.time_to_die);
    printf ("eat : %d\n", dainfo.time_to_eat);
    printf ("sleep : %d\n", dainfo.time_to_sleep);
    printf ("meals : %d\n", dainfo.number_of_times_each_philosopher_must_eat);
    printf ("forks : %d\n", dainfo.fork);
    int i = 0;
    t_philo tmp;
    while (i < dainfo.number_of_philosophers)
    {
        tmp = dainfo.philos[i];
        printf ("id %d is %d\n", i, tmp.id);
        i++;
    }
    // algo();

}
