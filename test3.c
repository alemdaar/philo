#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "header.h"


long long started_timimg()
{
    struct timeval current_time;
    if (gettimeofday(&current_time, NULL) == -1)
    {
        printf("gettimeofday failed\n");
        return 1;
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

int main ()
{
    t_info dainfo;
    long long now;

    dainfo.starting_time = started_timimg();
    now = 23;
    now = get_time(&dainfo);
    printf ("timme is : %lld\n", now);
}