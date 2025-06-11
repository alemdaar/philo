/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:12:45 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/11 22:48:20 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

int guarding(t_info *dainfo)
{
	
}

void *datask(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(&philo->meal_smp);
	philo->last_meal = get_time(philo->dainfo);
	sem_post(&philo->meal_smp);
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
        i++;
    }
    clean(dainfo);
}

int algo(t_info *dainfo)
{
    int	r;
	int	i;

	i = 0;
	dainfo->starting_time = started_timimg();
	r = pthread_create(&dainfo->guard, NULL, guarding, dainfo);
	if (r != SUCCESSFUL)
		return (output(ERR_CTH, 2), dainfo->trouble = -1, ERROR);
	sem_wait(&dainfo->philos[0].meal_smp);
	dainfo->starting_time = started_timimg();
	sem_post(&dainfo->philos[0].meal_smp);
	while (i < dainfo->number_of_philosophers)
	{
		dainfo->philos[i].pid = fork();
		if (dainfo->philos[i].pid == ERROR)
		{
			sem_wait(&dainfo->philos[0].meal_smp);
			dainfo->count_meal = 1;
			sem_post(&dainfo->philos[0].meal_smp);
			return (ERROR);
		}
		if (dainfo->philos[i].pid == SUCCESSFUL)
		{
			pthread_create(&dainfo->philos[i].thread, NULL, datask, &dainfo->philos[i]);
			pthread_join(dainfo->philos[i].thread, NULL);
			exit(SUCCESSFUL);
		}
		i++;
	}
	r = algo2(dainfo);
	return (r);
}
