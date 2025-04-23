#include "header.h"

int main (int ac, char **av)
{
    // number_of_philosophers time_to_die time_to_eat time_to_sleep
    // [number_of_times_each_philosopher_must_eat] (optional)
    kolshe stct ;
    if (ac != 5 && ac != 6)
        invalid_argc();
    parcing();
}
