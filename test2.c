#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *task(void *arg)
{
    int *data = (int *) arg;
    while (1)
    {
        if (*data != 1337)
        {
            printf ("no\n");
            return NULL;
        }
        else
            printf ("yes\n");
    }
    return NULL;
}

int main ()
{
    int data = 1337;
    pthread_t thread;
    int r = pthread_create(&thread, NULL, task, &data);
    if (r != 0)
    {
        printf ("thread failed !\n");
        return 1;
    }
    int tmp = 0;
    while (tmp < 100000000)
        tmp ++;
    data = -6;
    while (1);
    return 0;
}