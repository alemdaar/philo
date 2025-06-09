/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:56:47 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/09 22:35:03 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	*guarding(void *arg)
{
	t_info	*dainfo;
	int		must_eat;
	int		r;

	dainfo = (t_info *) arg;
	must_eat = dainfo->number_of_times_each_philosopher_must_eat;
	while (1)
	{
		r = guarding2(dainfo, must_eat);
		if (r == FAILED)
			return (NULL);
	}
	return (NULL);
}

void	*datask(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->dainfo->trouble == ERROR)
		return (NULL);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal = get_time(philo->dainfo);
	pthread_mutex_unlock(&philo->meal_mtx);
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
	r = pthread_create(&philo->thread, NULL, onephilo_task, philo);
	if (r != SUCCESSFUL)
	{
		output("Error creating thread\n", 2);
		return (dainfo->trouble = -1, ERROR);
	}
	r = pthread_join(philo->thread, NULL);
	if (r != SUCCESSFUL)
		return (output("Error: waiting thread", 2), ERROR);
	return (SUCCESSFUL);
}

int	algo(t_philo *philo, t_info *dainfo)
{
	int	r;
	int	i;

	i = 0;
	dainfo->starting_time = started_timimg();
	r = pthread_create(&dainfo->gaurd, NULL, guarding, dainfo);
	if (r != SUCCESSFUL)
		return (output(ERR_CTH, 2), dainfo->trouble = -1, ERROR);
	while (i < dainfo->number_of_philosophers)
	{
		pthread_create(&philo[i].thread, NULL, datask, &philo[i]);
		i++;
	}
	r = pthread_join(dainfo->gaurd, NULL);
	if (r != SUCCESSFUL)
		return (output(ERR_JTH, 2), ERROR);
	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		r = pthread_join(philo[i++].thread, NULL);
		if (r != SUCCESSFUL)
			return (output("Error: waiting thread", 2), ERROR);
	}
	return (SUCCESSFUL);
}
