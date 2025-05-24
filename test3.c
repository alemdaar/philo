#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *task(void *arg)
{
    printf ("123456789\n");
    pthread_mutex_t *mutex = (pthread_mutex_t *) arg;
    pthread_mutex_lock(mutex);
    printf ("hello\n");
    int tmp = 0;
    while (tmp < 1)
        tmp ++;
    printf ("man\n");
    pthread_mutex_unlock(mutex);
    return NULL;
}

int main ()
{
    pthread_t thread, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
    pthread_mutex_t mutex;
    int r = pthread_mutex_init(&mutex, NULL);
	if (r != 0)
		return(printf("Failed to initialize mutex.\n"), 1);
    r = pthread_create(&thread, NULL, task, &mutex);
    if (r != 0)
    {
        printf ("thread failed !\n");
        return 1;
    }
    r = pthread_create(&thread2, NULL, task, &mutex);
    if (r != 0)
    {
        printf ("thread 2 failed !\n");
        return 1;
    }
    r = pthread_create(&thread3, NULL, task, &mutex);
    if (r != 0)
    {
        printf ("thread 2 failed !\n");
        return 1;
    }
    r = pthread_create(&thread4, NULL, task, &mutex);
    if (r != 0)
    {
        printf ("thread 2 failed !\n");
        return 1;
    }
    r = pthread_create(&thread5, NULL, task, &mutex);
    if (r != 0)
    {
        printf ("thread 2 failed !\n");
        return 1;
    }
    r = pthread_create(&thread6, NULL, task, &mutex);
    if (r != 0)
    {
        printf ("thread 2 failed !\n");
        return 1;
    }
    r = pthread_create(&thread7, NULL, task, &mutex);
    if (r != 0)
    {
        printf ("thread 2 failed !\n");
        return 1;
    }
    r = pthread_create(&thread8, NULL, task, &mutex);
    if (r != 0)
    {
        printf ("thread 2 failed !\n");
        return 1;
    }
    r = pthread_create(&thread9, NULL, task, &mutex);
    if (r != 0)
    {
        printf ("thread 2 failed !\n");
        return 1;
    }
    while (1);
    return 0;
}