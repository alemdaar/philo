void *datask(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // pthread_mutex_lock(&philo->dainfo->write);
    // printf("inside : %d\n", philo->id);
    // pthread_mutex_unlock(&philo->dainfo->write);

    if (philo->id % 2 == 0) // 2 4
    {
        usleep(1000);
        while (1)
        {
            pthread_mutex_lock(&philo->dainfo->write);//
            printf("%d %d dkhal\n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);//

            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);//                              |     - lock right
            pthread_mutex_lock(&philo->dainfo->write);//
            printf("%d %d +++++++++++++++++++++\n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);//
            pthread_mutex_lock(&philo->dainfo->write);//                                                  |     |   - lock write
            printf("%d %d took right fork -> %d\n", get_time(philo->dainfo->starting_time), philo->id, philo->fork[RIGHT]);//       |     |   |   print
            pthread_mutex_unlock(&philo->dainfo->write);//                                                |     |   * unlock write
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);//                               |     |   - lock left
            pthread_mutex_lock(&philo->dainfo->write);//                                                  |     |   |   - lock write
            printf("%d %d took left fork -> %d\n", get_time(philo->dainfo->starting_time), philo->id, philo->fork[LEFT]);//        |     |   |   |   print
            pthread_mutex_unlock(&philo->dainfo->write);//                                                |     |   |   * unlock write
            pthread_mutex_lock(&philo->dainfo->write);//                                                  |     |   |   - lock write
            printf("%d %d is eating\n", get_time(philo->dainfo->starting_time), philo->id);//             |     |   |   |   print
            pthread_mutex_unlock(&philo->dainfo->write);//                                                |     |   |   * unlock write
            usleep(1000000);//                                                                            |     |   |   sleep
            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);//                             |     |   * unlock left
            pthread_mutex_lock(&philo->dainfo->write);//                                                  |     |   - lock write
            printf("%d %d leaves left fork -> %d\n", get_time(philo->dainfo->starting_time), philo->id, philo->fork[LEFT]);//      |     |   |   print
            pthread_mutex_unlock(&philo->dainfo->write);//                                                |     |   * unlock write
            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);//                            |     * unlock left
            pthread_mutex_lock(&philo->dainfo->write);//                                                  |     - lock write
            printf("%d %d leaves right fork -> %d\n", get_time(philo->dainfo->starting_time), philo->id, philo->fork[RIGHT]);//     |     |   print
            pthread_mutex_unlock(&philo->dainfo->write);//                                                |     * lock write

            pthread_mutex_lock(&philo->dainfo->write);//                                                |     |   * unlock write
            printf("%d %d slept\n", get_time(philo->dainfo->starting_time), philo->id);//     |     |   print
            pthread_mutex_unlock(&philo->dainfo->write);//                                                |     |   * unlock write
            usleep(500000);//                                                                            |     think
        }
    }
    else // 1 3 5 
    {
        while (1) 
        {
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d took left fork else -> %d\n", get_time(philo->dainfo->starting_time), philo->id, philo->fork[LEFT]);//        |     |   |   |   print
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d took right fork else -> %d\n", get_time(philo->dainfo->starting_time), philo->id, philo->fork[RIGHT]);//       |     |   |   print
            pthread_mutex_unlock(&philo->dainfo->write);
            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d is eating else \n", get_time(philo->dainfo->starting_time), philo->id);
            pthread_mutex_unlock(&philo->dainfo->write);
            usleep(1000000);

            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);

            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d leaves right fork else -> %d\n", get_time(philo->dainfo->starting_time), philo->id, philo->fork[RIGHT]);//     |     |   print
            pthread_mutex_unlock(&philo->dainfo->write);

            pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);

            pthread_mutex_lock(&philo->dainfo->write);
            printf("%d %d leaves left fork else -> %d\n", get_time(philo->dainfo->starting_time), philo->id, philo->fork[LEFT]);//      |     |   |   print
            pthread_mutex_unlock(&philo->dainfo->write);

            pthread_mutex_lock(&philo->dainfo->write);//                                                |     |   * unlock write
            printf("%d %d slept\n", get_time(philo->dainfo->starting_time), philo->id);//     |     |   print
            pthread_mutex_unlock(&philo->dainfo->write);//                                                |     |   * unlock write
            usleep(500000);//                                                                            |     think
        }
    }
    return NULL;
}