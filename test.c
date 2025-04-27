#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for sleep()

// Function that will be executed by the first thread
void* thread_function1(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 1: Message %d\n", i+1);
        sleep(1); // Sleep for 1 second
    }
    return NULL;
}

// Function that will be executed by the second thread
void* thread_function2(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 2: Message %d\n", i+1);
        sleep(2); // Sleep for 2 seconds
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    printf("Main: Creating threads...\n");
    
    // Create thread 1
    if (pthread_create(&thread1, NULL, thread_function1, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    
    // Create thread 2
    if (pthread_create(&thread2, NULL, thread_function2, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    
    printf("Main: Threads created. Waiting for them to finish...\n");
    
    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Main: Both threads have finished.\n");
    
    return 0;
}