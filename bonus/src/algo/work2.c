/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:36:31 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/12 22:52:20 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

int	thinking(t_philo *philo, long long date)
{
	status(philo, THINK, date);
	return (SUCCESSFUL);
}

int	sleeping(t_philo *philo, long long date)
{
	status(philo, SLEEP, date);
	holding(philo, philo->dainfo->time_to_sleep);
	return (SUCCESSFUL);
}

int	eating(t_philo *philo)
{
	int	r;

	// printf ("philo %d wants right fork\n", philo->id);
	sem_wait(philo->dainfo->forks);
	status(philo, FORK, get_time(philo->dainfo));
	// printf ("philo %d wants left fork\n", philo->id);
	sem_wait(philo->dainfo->forks);
	status(philo, FORK, get_time(philo->dainfo));
	sem_wait(philo->health_smp);
	// printf ("philo %d health 0\n", philo->id);
	philo->health = 0;
	sem_post(philo->health_smp);
	sem_wait(philo->meal_smp);
	// printf ("philo %d last meal\n", philo->id);
	philo->last_meal = get_time(philo->dainfo);
	sem_post(philo->meal_smp);
	status(philo, EAT, get_time(philo->dainfo));
	r = holding(philo, philo->dainfo->time_to_eat);
	if (r == FAILED)
	{
		sem_post(philo->dainfo->forks);
		sem_post(philo->dainfo->forks);
		return (FAILED);
	}
	sem_post(philo->dainfo->forks);
	return (sem_post(philo->dainfo->forks), 0);
}

int	endless(t_philo *philo)
{
	int	r;

	while (1)
	{
		printf ("philo : %d\n", philo->id);
		r = eating(philo);
		if (r == FAILED)
			return (FAILED);
		sleeping(philo, get_time(philo->dainfo));
		thinking(philo, get_time(philo->dainfo));
	}
	return (SUCCESSFUL);
}

int	limited(t_philo *philo)
{
	int	i;
	int	r;

	i = 0;
	while (i < philo->dainfo->number_of_times_each_philosopher_must_eat)
	{
		r = eating(philo);
		if (r == FAILED)
			return (FAILED);
		sleeping(philo, get_time(philo->dainfo));
		thinking(philo, get_time(philo->dainfo));
		i++;
	}
	sem_wait(philo->dainfo->count_smp);
	status(philo, "wsal hna", get_time(philo->dainfo));
	if (philo->dainfo->count_meal == 0)
	{
		philo->dainfo->count_meal = 1;
		sem_post(philo->dainfo->count_smp);
		status(philo, "HERE 1", get_time(philo->dainfo));
		return (SUCCESSFUL);
	}
	sem_post(philo->dainfo->count_smp);
	status(philo, "HERE 2", get_time(philo->dainfo));
	return (SUCCESSFUL);
}
