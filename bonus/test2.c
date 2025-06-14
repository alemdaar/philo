#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

#define SUCCESSFUL 0
#define FAILURE 1

int semaphores(t_info *dainfo)
{
    char sem_name[64];
    int i;

    // Unlink old semaphores (optional but recommended)
    sem_unlink("/forks");
    sem_unlink("/death_smp");
    sem_unlink("/count_smp");
    for (i = 0; i < dainfo->number_of_philosophers; i++) {
        snprintf(sem_name, sizeof(sem_name), "/health_%d", i);
        sem_unlink(sem_name);
        snprintf(sem_name, sizeof(sem_name), "/meal_%d", i);
        sem_unlink(sem_name);
    }

    dainfo->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, dainfo->number_of_philosophers);
    if (dainfo->forks == SEM_FAILED) {
        perror("sem_open /forks failed");
        return FAILURE;
    }

    dainfo->death_smp = sem_open("/death_smp", O_CREAT | O_EXCL, 0644, 1);
    if (dainfo->death_smp == SEM_FAILED) {
        perror("sem_open /death_smp failed");
        return FAILURE;
    }

    dainfo->count_smp = sem_open("/count_smp", O_CREAT | O_EXCL, 0644, 1);
    if (dainfo->count_smp == SEM_FAILED) {
        perror("sem_open /count_smp failed");
        return FAILURE;
    }

    for (i = 0; i < dainfo->number_of_philosophers; i++) {
        snprintf(sem_name, sizeof(sem_name), "/health_%d", i);
        dainfo->philos[i].health_smp = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
        if (dainfo->philos[i].health_smp == SEM_FAILED) {
            perror(sem_name);
            return FAILURE;
        }

        snprintf(sem_name, sizeof(sem_name), "/meal_%d", i);
        dainfo->philos[i].meal_smp = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
        if (dainfo->philos[i].meal_smp == SEM_FAILED) {
            perror(sem_name);
            return FAILURE;
        }
    }

    return SUCCESSFUL;
}
