#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
// size_t mails = 0;

void* routine(void* arg) {
    // int c = 0;
    int *hold = (int *)arg;
    printf ("before : %d\n", *hold);
    // printf ("entered\n");
    for (size_t i = 0; i < 10000000; i++) {
        // pthread_mutex_lock(&mutex);
        *hold+=1;
        fprintf (stdout, "after : %d\n", *hold);
        while (1);
        // pthread_mutex_unlock(&mutex);
        // if (c == 0) {
        //     printf ("strated\n");
        //     c = 1;
        // }
    }
    printf ("here\n");
    printf ("finished\n");
    return NULL;
}

int main() {
    pthread_t p1, p2, p3, p4, p5, p6;
    size_t mails = 0;
    // int i = 0;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&p1, NULL, routine, &mails) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    if (pthread_create(&p2, NULL, routine, &mails) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    if (pthread_create(&p3, NULL, routine, &mails) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    if (pthread_create(&p4, NULL, routine, &mails) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    if (pthread_create(&p5, NULL, routine, &mails) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    if (pthread_create(&p6, NULL, routine, &mails) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    if (pthread_join(p1, NULL) != 0) {
        printf ("join 1 failed\n");
        return 1;
    }
    if (pthread_join(p2, NULL) != 0) {
        printf ("join 2 failed\n");
        return 1;
    }
    if (pthread_join(p3, NULL) != 0) {
        printf ("join 2 failed\n");
        return 1;
    }
    if (pthread_join(p4, NULL) != 0) {
        printf ("join 2 failed\n");
        return 1;
    }
    if (pthread_join(p5, NULL) != 0) {
        printf ("join 2 failed\n");
        return 1;
    }
    if (pthread_join(p6, NULL) != 0) {
        printf ("join 2 failed\n");
        return 1;
    }

    pthread_mutex_destroy(&mutex);
    printf ("mails : %zu\n", mails);
    return 0;
}