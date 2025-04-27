#include "../../header.h"

void algo()
{
    int r;
    while (1)
    {
        r = pthread_create(&philo, NULL, thread_function2, NULL);
        if ( != 0) {
            fprintf(stderr, "Error creating thread 2\n");
            return 1;
        }
        printf("Main: Threads created. Waiting for them to finish...\n");

        // Wait for both threads to finish
        pthread_join(thread1, NULL);
    }
}