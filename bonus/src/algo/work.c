/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:12:45 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/14 22:52:06 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

void	*guarding(void *arg)
{
	t_philo	*philo;
	int	health;
	int		r;
	int		i;

	while (1)
	{
		sem_wait(philo->count_smp);
		write (1, ".\n", 2);
		if (philo->count_meal == 1)
			return (NULL);
		sem_post(philo->count_smp);
		sem_wait(philo->meal_smp);
		health = (get_time(philo->dainfo) - philo->last_meal);
		sem_post(philo->meal_smp);
		sem_wait(philo->health_smp);
		philo->health = health;
		if (philo->health >= philo->dainfo->time_to_die)
		{
			sem_wait(philo->dainfo->write);
			printf ("%lld %d died\n", get_time(philo->dainfo), i + 1);
			sem_post(philo->dainfo->write);
			return (sem_post(philo->health_smp), exit(0), NULL);
		}
		sem_post(philo->health_smp);
	}
	return (NULL);
}

void	*onephilo_task(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->dainfo->starting_time = started_timimg();
	printf("%lld %d %s\n", get_time(philo->dainfo), philo->id, FORK);
	holding(philo, philo->dainfo->time_to_die);
	printf("%lld %d %s\n", get_time(philo->dainfo), philo->id, DYING);
	return (NULL);
}

int	one_philo(t_philo *philo, t_info *dainfo)
{
	int	r;
	int	i;

	i = 0;
	philo->pid = fork();
	if (philo->pid == ERROR)
		return (ERROR);
	if (philo->pid == SUCCESSFUL)
	{
		r = pthread_create(&philo->thread, NULL, onephilo_task, philo);
		if (r != SUCCESSFUL)
		{
			output("Error creating thread\n", 2);
			return (ERROR);
		}
		else
		{
			r = pthread_join(philo->thread, NULL);
			if (r != SUCCESSFUL)
				return (output("Error: waiting thread", 2), ERROR);		
		}
	}
	wait(NULL);
	return (SUCCESSFUL);
}

void *datask(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->meal_smp);
	philo->last_meal = get_time(philo->dainfo);
	sem_post(philo->meal_smp);
	if (philo->id % 2 == 0)
	{
		status(philo, THINK, get_time(philo->dainfo));
		holding(philo, philo->dainfo->time_to_eat / 2);
	}
	if (philo->dainfo->nb_of_inputs == 4)
		endless(philo);
	else
		limited(philo);
	return (NULL);
}

int	algo2(t_info *dainfo)
{
	int	i;

	i = 0;
	while (i < dainfo->number_of_philosophers)
    {
        wait(NULL);
		write (1, "Y\n", 2);
        i++;
    }
	write (1, "Z\n", 2);
    clean(dainfo);
	return (SUCCESSFUL);
}

int algo(t_info *dainfo)
{
    int	r;
	int	i;

	i = 0;
	dainfo->starting_time = started_timimg();
	while (i < dainfo->number_of_philosophers)
	{
		dainfo->philos[i].pid = fork();
		if (dainfo->philos[i].pid == ERROR)
			return (clean(dainfo), exit(FAILED), ERROR);
		if (dainfo->philos[i].pid == SUCCESSFUL)
		{
			write (1, "B\n", 2);
			pthread_create(&dainfo->guard, NULL, guarding, &dainfo->philos[i]);
			pthread_create(&dainfo->philos[i].thread, NULL, datask, &dainfo->philos[i]);
			pthread_join(dainfo->guard, NULL);
			pthread_join(dainfo->philos[i].thread, NULL);
			exit(SUCCESSFUL);
		}
		i++;
	}
	r = algo2(dainfo);
	return (r);
}
