/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:36:31 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/15 19:58:59 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

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

	pthread_mutex_lock(&philo->dainfo->forks[philo->fork[RIGHT]]);
	status(philo, FORK, get_time(philo->dainfo));
	pthread_mutex_lock(&philo->dainfo->forks[philo->fork[LEFT]]);
	status(philo, FORK, get_time(philo->dainfo));
	pthread_mutex_lock(&philo->health_mtx);
	philo->health = 0;
	pthread_mutex_unlock(&philo->health_mtx);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal = get_time(philo->dainfo);
	pthread_mutex_unlock(&philo->meal_mtx);
	status(philo, EAT, get_time(philo->dainfo));
	r = holding(philo, philo->dainfo->time_to_eat);
	if (r == FAILED)
	{
		pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[RIGHT]]);
		pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
		return (FAILED);
	}
	pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[LEFT]]);
	return (pthread_mutex_unlock(&philo->dainfo->forks[philo->fork[0]]), 0);
}

int	endless(t_philo *philo)
{
	int	r;

	while (1)
	{
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
	pthread_mutex_lock(&philo->dainfo->count_mtx);
	if (philo->dainfo->count_meal == 0)
	{
		philo->dainfo->count_meal = 1;
		pthread_mutex_unlock(&philo->dainfo->count_mtx);
		return (SUCCESSFUL);
	}
	pthread_mutex_unlock(&philo->dainfo->count_mtx);
	return (SUCCESSFUL);
}
