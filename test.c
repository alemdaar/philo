// printf ("philos : %d\n", dainfo.number_of_philosophers);
    // printf ("die : %d\n", dainfo.time_to_die);
    // printf ("eat : %d\n", dainfo.time_to_eat);
    // printf ("sleep : %d\n", dainfo.time_to_sleep);
    // printf ("meals : %d\n", dainfo.number_of_times_each_philosopher_must_eat);
    // int i = 0;
    // t_philo *tmp;
    // while (i < dainfo.number_of_philosophers)
    // {
    //     tmp = &dainfo.philos[i];
    //     // printf ("id %d is %d\n", i, tmp->id);
    //     printf ("id %d is %d\n", i, tmp->id);
    //     i++;
    // }
    // i = 0;
    // while (i < dainfo.number_of_philosophers)
    // {
    //     printf ("left %d right %d\n", i, philo[i].fork[LEFT], philo[i].fork[RIGHT]);
    //     i++;
    // }
    // printf ("checked main\n");
#include <pthread.h>
#include <stdio.h>

int main() {
    pthread_mutex_t mutex; // uninitialized!
    int result = pthread_mutex_destroy(&mutex);

    if (result != 0) {
        perror("pthread_mutex_destroy");
    } else {
        printf("Mutex destroyed.\n");
    }

    return 0;
}
