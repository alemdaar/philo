#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

#define NUM_PHILOSOPHERS 5

sem_t *forks;
sem_t *print;

void cleanup_semaphores() {
    sem_unlink("/forks");
    sem_unlink("/print");
}

void philosopher_routine(int id) {
    while (1) {
        // Thinking
        sem_wait(print);
        printf("Philosopher %d is thinking\n", id);
        sem_post(print);
        usleep(50000);  // 0.5s

        // Take forks (we take two from the pool of N forks)
        sem_wait(forks);
        sem_wait(forks);

        sem_wait(print);
        printf("Philosopher %d has taken two forks\n", id);
        printf("Philosopher %d is eating\n", id);
        sem_post(print);

        usleep(100000);  // 1s

        // Put down forks
        sem_post(forks);
        sem_post(forks);

        sem_wait(print);
        printf("Philosopher %d has finished eating\n", id);
        sem_post(print);

        usleep(500);  // 0.5s
    }
}

int main(void) {
    // Cleanup any leftover semaphores from previous runs
    cleanup_semaphores();

    // Initialize semaphores
    char *str = "/forks";
    char *str2 = "/print";
    forks = sem_open(str, O_CREAT, 0644, NUM_PHILOSOPHERS);
    print = sem_open(str2, O_CREAT, 0644, 1);

    if (forks == SEM_FAILED || print == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    // Create philosopher processes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pid_t pid = fork();
        if (pid == 0)
        {
            philosopher_routine(i + 1);
            exit(0);
        }
    }

    // Parent waits for any child (or just sleeps forever if sim never ends)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        wait(NULL);
    }

    // Cleanup
    sem_close(forks);
    sem_close(print);
    cleanup_semaphores();

    return 0;
}
