/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:16 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/09 22:35:07 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	guarding2(t_info *dainfo, int must_eat)
{
	int	i;
	int	health;

	i = 0;
	pthread_mutex_lock(&dainfo->count_mtx);
	if (dainfo->philos[0].count_meals == must_eat)
		return (FAILED);
	pthread_mutex_unlock(&dainfo->count_mtx);
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
