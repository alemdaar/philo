#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

size_t mails = 0;

void* routine(void* arg) {
    char *tmp = (char *) arg;
    write (1, "e\n", 2);
    pthread_mutex_lock(&mutex);
    write (1, tmp, 2);
    int long long num = 0;
    while (num < 10000000000)
        num++;
    pthread_mutex_unlock(&mutex);
    write (1, "f\n", 2);
    // write (1, "l\n", 2);
    return NULL;
}

int main() {
    pthread_t p1, p2, p3;
    char * a1;
    char * a2;
    char * a3;
    a1 = "1\n";
    a2 = "2\n";
    a3 = "3\n";
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Failed to initialize mutex.\n");
        return 1;
    }

    if (pthread_create(&p1, NULL, routine, a1) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    if (pthread_create(&p2, NULL, routine, a2) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    if (pthread_create(&p3, NULL, routine, a3) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    // int long long tmp = 0;
    // while (tmp < 3000000000)
    //     tmp++;
    if (pthread_join(p1, NULL) != 0) {
        printf ("join 1 failed\n");
        return 1;
    }
    if (pthread_join(p2, NULL) != 0) {
        printf ("join 2 failed\n");
        return 1;
    }
    if (pthread_join(p3, NULL) != 0) {
        printf ("join 3 failed\n");
        return 1;
    }
    pthread_mutex_destroy(&mutex);
    printf ("mails : %zu\n", mails);
    return 0;
}