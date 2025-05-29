#include "../../header.h"

int is_number(char *str)
{
    int i;
    i = 0;
	if (!str[0])
		why_exit("one of the args is empty\n", FAILED);
    if (str[i] IS '+' || str[i] IS '-')
        i++;
    if (!str[i])
        return 0;
    while (str[i])
    {
        if (str[i] < '0' OR str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int set_mutex(t_info *dainfo)
{
	int i = 0;
	int r;
	r = pthread_mutex_init(&dainfo->write, NULL);
	if (r NOT SUCCESSFUL)
		return (output("Failed to initialize mutex.\n", 2), FAILED);
	while (i < dainfo->number_of_philosophers)
	{
		r = pthread_mutex_init(&dainfo->forks[i], NULL);
		if (r NOT SUCCESSFUL)
			return (output("Failed to initialize mutex.\n", 2), FAILED);
		i++;
	}
	return SUCCESSFUL;
}

int set_info(t_info *dainfo, t_philo **philo)
{
	dainfo->number_of_philosophers = dainfo->tmp_nb[0];
	dainfo->time_to_die = dainfo->tmp_nb[1];
	dainfo->time_to_eat = dainfo->tmp_nb[2];
	dainfo->time_to_sleep = dainfo->tmp_nb[3];

	if (dainfo->nb_of_inputs == 5)
		dainfo->number_of_times_each_philosopher_must_eat = dainfo->tmp_nb[4];

	dainfo->forks = malloc (sizeof(pthread_mutex_t) * dainfo->number_of_philosophers);
	if (!dainfo->forks)
		return (output("memory allocation failed\n", 2), FAILED);

	philo[0] = malloc (sizeof(t_philo) * dainfo->number_of_philosophers);
	if (!philo[0])
	{
		// free_all(dainfo->forks);
		return (output("memory allocation failed\n", 2), FAILED);
	}

	philo[0]->count_meals = 0;

	dainfo->death = 0;

	dainfo->died_id = -1;

	dainfo->trouble = 0;

	dainfo->philos = philo[0];
	return 0;
}

int	parcing(int ac, char **av, t_info *dainfo)
{
	int i;
	int r;
	i = 1;
	while (i < ac)
	{
		// printf ("input %d: %s\n", i, av[i]);
		r = is_number(av[i]);
		if (r == 0)
		    return (output("the input is not a number\n", 2), FAILED);
		dainfo->tmp_nb[i - 1] = myatoi(av[i]);
		if (dainfo->tmp_nb[i - 1] < 0)
		    return (output("the input contains a negative number\n", 2), FAILED);
		// printf ("nb :     %lld\n", nb[i - 1]);
		if (i != 5 && dainfo->tmp_nb[i - 1] == 0)
		    return (output("one of the inputs is 0\n", 2), FAILED);
		i++;
	}
	if (ac == 5)
		dainfo->number_of_times_each_philosopher_must_eat = -1;
	dainfo->nb_of_inputs = ac - 1;
	return SUCCESSFUL;
}

int set_philos(t_info *dainfo, t_philo **philo)
{
	int	i;

	i = 0;
	// t_philo *tmp_philo;
	while (i < dainfo->number_of_philosophers)
	{
		// tmp_philo = &dainfo->philos[i];
		philo[0][i].id = i + 1;
		if (philo[0][i].id == 1)
			philo[0][i].fork[0] = dainfo->number_of_philosophers - 1;
		else
			philo[0][i].fork[0] = philo[0][i].id - 2;
		philo[0][i].fork[1] = philo[0][i].id - 1;
		philo[0][i].fork[1] = philo[0][i].id - 1;
		philo[0][i].last_meal = -1;
		philo[0][i].health = 0;
		philo[0][i].dainfo = dainfo;
		// printf ("left %d right %d\n", philo[0][i].fork[1], philo[0][i].fork[0]);
		i++;
	}
	return SUCCESSFUL;
}

int	init(int ac, char **av, t_info *dainfo, t_philo **philo)
{
	int r;

	r = set_info(dainfo, philo);
	if (r IS FAILED)
		return (FAILED);
	r = set_mutex(dainfo);
	if (r IS FAILED)
		return (FAILED);
	r = set_philos(dainfo, philo);
	if (r IS FAILED)
		return (FAILED);
	return SUCCESSFUL;
}
