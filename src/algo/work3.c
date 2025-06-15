/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:16 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/15 20:01:59 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"
#include <fcntl.h>

static int	guarding3(t_info *dainfo)
{
	pthread_mutex_lock(&dainfo->count_mtx);
	if (dainfo->count_meal == 1)
	{
		pthread_mutex_unlock(&dainfo->count_mtx);
		return (SUCCESSFUL);
	}
	pthread_mutex_unlock(&dainfo->count_mtx);
	return (3);
}

int	guarding2(t_info *dainfo)
{
	int	i;
	int	health;

	i = guarding3(dainfo);
	if (i == SUCCESSFUL)
		return (FAILED);
	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		pthread_mutex_lock(&dainfo->philos[i].meal_mtx);
		health = (get_time(dainfo) - dainfo->philos[i].last_meal);
		pthread_mutex_unlock(&dainfo->philos[i].meal_mtx);
		pthread_mutex_lock(&dainfo->philos[i].health_mtx);
		dainfo->philos[i].health = health;
		if (dainfo->philos[i].health >= dainfo->time_to_die)
		{
			pthread_mutex_lock(&dainfo->death_mtx);
			dainfo->death = 1;
			printf ("%lld %d died\n", get_time(dainfo), i + 1);
			pthread_mutex_unlock(&dainfo->death_mtx);
			return (pthread_mutex_unlock(&dainfo->philos[i].health_mtx), 1);
		}
		pthread_mutex_unlock(&dainfo->philos[i++].health_mtx);
	}
	return (SUCCESSFUL);
}

int	algo2(t_philo *philo, t_info *dainfo)
{
	int	r;
	int	i;

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
