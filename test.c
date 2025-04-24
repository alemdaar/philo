#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep()

// Function that the first thread will execute
void* thread1_task(void* arg) {
    int *a = arg;
    printf ("a in thread %d\n", *a);
    return NULL;
}

// Function that the second thread will execute
// void* thread2_task(void* arg) {
//     int *a = arg;
//     printf ("a in thread 2 is : %d\n", *a);
//     *a += 1;
//     printf ("2 a in thread 2 is : %d\n", *a);
//     return NULL;
// }

int main() {
    pthread_t thread1, thread2;

    printf ("1 ..\n");
    int a = 10;
    int r1 = pthread_create(&thread1, NULL, thread1_task, &a);
    int long long  i = 0;
    while (i < 5999999999)
    {
        i++;
    }
    a++;
    printf ("1 created\n");
    // printf ("a in main is : %d\n", a);
    if (r1 != 0) {
        perror("Failed to create Thread 1");
        return 1;
    }
    // printf ("2 ...\n");
    // int r2 = pthread_create(&thread2, NULL, thread2_task, NULL);
    // printf ("2 created\n");
    // if (r2 != 0) {
    //     perror("Failed to create Thread 2");
    //     return 1;
    // }
    printf ("a in main %d\n", a);
    printf ("qbl wait\n");
    pthread_join(thread1, NULL);
    // printf ("between wait\n");
    // pthread_join(thread2, NULL);

    printf("Main thread: Both threads have finished.\n");
    return 0;
}