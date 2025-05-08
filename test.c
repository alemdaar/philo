#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
size_t mails = 0;

void* routine(void* arg) {
    char s = mails + 65;
    write (1, &s, 1);
    write (1, "\n", 1);
    write (1, "e\n", 2);
    pthread_mutex_lock(&mutex);
    int c = 0;
    for (size_t i = 0; i < 1000000; i++) {
        mails += 1;
        // fprintf (stdout, "after : %zu\n", mails);
        if (c == 0)
        {
            write (1, "s\n", 2);
            c = 1;
        }
    }
    write (1, "f\n", 2);
    pthread_mutex_unlock(&mutex);
    // write (1, "l\n", 2);
    return NULL;
}

int main() {
    pthread_t p1, p2;

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Failed to initialize mutex.\n");
        return 1;
    }

    if (pthread_create(&p1, NULL, routine, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    if (pthread_create(&p2, NULL, routine, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    int long long tmp = 0;
    while (tmp < 3000000000)
        tmp++;
    if (pthread_join(p1, NULL) != 0) {
        printf ("join 1 failed\n");
        return 1;
    }
    else
    {
        printf ("first join\n");
    }
    if (pthread_join(p2, NULL) != 0) {
        printf ("join 2 failed\n");
        return 1;
    }
    else
        printf ("second join\n");
    pthread_mutex_destroy(&mutex);
    printf ("mails : %zu\n", mails);
    return 0;
}