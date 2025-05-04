#include "../../header.h"

int is_number(char *str)
{
    int i;
    i = 0;
	if (!str[0])
		why_exit("one of the args is empty\n", FAILED);
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!str[i])
        return 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int set_info(t_info *dainfo, long long int nb[5])
{
	// number_of_philosophers time_to_die time_to_eat time_to_sleep
    // [number_of_times_each_philosopher_must_eat] (optional)
	dainfo->number_of_philosophers = nb[0];
	dainfo->time_to_die = nb[1];
	dainfo->time_to_eat = nb[2];
	dainfo->time_to_sleep = nb[3];
	if (dainfo->nb_of_inputs == 5)
		dainfo->number_of_times_each_philosopher_must_eat = nb[4];
	dainfo->pair = 0;
	dainfo->forks = malloc (sizeof(t_philo) * dainfo->number_of_philosophers);
	if (!dainfo->forks)
		return (why_exit("memory allocation failed\n", 1), FAILED);
	dainfo->philos = malloc (sizeof(t_philo) * dainfo->number_of_philosophers);
	if (!dainfo->philos)
	{
		// free_all(dainfo->philos);
		return (why_exit("memory allocation failed\n", 1), FAILED);
	}
	return 0;
}

void    check_input(int ac, char **av, t_info *dainfo)
{
	int i;
	int r;
	i = 1;
	long long int nb[5];
	while (i < ac)
	{
		printf ("input %d: %s\n", i, av[i]);
		r = is_number(av[i]);
		if (r == 0)
		    why_exit("the input is not a number\n", FAILED);
		nb[i - 1] = myatoi(av[i]);
		printf ("nb :     %lld\n", nb[i - 1]);
		if (i != 5 && nb[i - 1] == 0)
		    why_exit("one of the inputs is 0\n", FAILED);
		i++;
	}
	if (ac == 5)
		dainfo->number_of_times_each_philosopher_must_eat = -1;
	dainfo->nb_of_inputs = ac - 1;
	set_info(dainfo, nb);
	return;
}

void set_philos(t_info *dainfo, t_philo *philo)
{
	int	i;

	i = 0;
	t_philo *tmp_philo;
	while (i < dainfo->number_of_philosophers)
	{
		tmp_philo = &dainfo->philos[i];
		tmp_philo->id = i;
		tmp_philo->fork[RIGHT] = -1;
		tmp_philo->fork[LEFT] = -1;
		dainfo->forks[i] = i;
        // printf ("id %d is %d\n", i, tmp_philo->id);
		i++;
	}
    // printf ("intial\n");
	// i = 0;
	// while (i < dainfo->number_of_philosophers)
	// {
	// 	tmp_philo = &dainfo->philos[i];
    //     printf ("id %d is %d---------- address : %p\n", i, tmp_philo->id, tmp_philo);
	// 	i++;
	// }
    // printf ("checked same ptr\n");
	// tmp_philo = &dainfo->philos[4];
    // printf ("id %d is %d,----------+++++++\n", 4, tmp_philo->id);
	// i = 0;
    // t_philo *tmp;
    // while (i < dainfo->number_of_philosophers)
    // {
    //     tmp = &dainfo->philos[i];
    //     printf ("id %d is %d,    address : %p\n", i, tmp->id, tmp);
    //     i++;
    // }
	// printf ("checked another ptr\n");
}

// int set_philos_forks(t_info *dainfo, t_philo *philo)
// {
// 	int	i;
// 	t_philo *tmp_philo;

// 	i = 0;
// 	while (i < dainfo->number_of_philosophers)
// 	{
// 		tmp_philo = &philo[i];

// 		i++;
// 	}
// }

void	parcing(int ac, char **av, t_info *dainfo, t_philo *philo)
{
	check_input(ac, av, dainfo);
	set_philos(dainfo, philo);
}
