#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
size_t mails = 0;

void* routine(void* arg) {
    printf ("entered\n");
    pthread_mutex_lock(&mutex);
    int c = 0;
    for (size_t i = 0; i < 10000; i++) {
        mails += 1;
        // fprintf (stdout, "after : %zu\n", mails);
        if (c == 0)
        {
            printf ("strated\n");
            c = 1;
        }
    }
    pthread_mutex_unlock(&mutex);
    printf ("finished\n");
    return NULL;
}

int main() {
    int t = 0;
    pthread_t p1, p2, p3, p4, p5, p6;
    if (pthread_create(&p1, NULL, routine, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    if (pthread_create(&p2, NULL, routine, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    if (pthread_create(&p3, NULL, routine, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    if (pthread_create(&p4, NULL, routine, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    if (pthread_create(&p5, NULL, routine, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    if (pthread_create(&p6, NULL, routine, NULL) != 0) {
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