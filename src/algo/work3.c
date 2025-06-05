/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:16 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/05 18:57:34 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	guarding2(t_info *dainfo, int must_eat)
{
	int	i;
	int	health;

	i = 0;
	if (dainfo->philos[i].count_meals == must_eat)
		return (FAILED);
	while (i < dainfo->number_of_philosophers)
	{
		pthread_mutex_lock(&dainfo->philos[i].health_mtx);
		health = (get_time(dainfo) - dainfo->philos[i].last_meal);
		dainfo->philos[i].health = health;
		if (dainfo->philos[i].health >= dainfo->time_to_die)
		{
			pthread_mutex_lock(&dainfo->death_mtx);
			dainfo->death = 1;
			printf ("%lld %d died\n", get_time(dainfo), i + 1);
			pthread_mutex_unlock(&dainfo->death_mtx);
			pthread_mutex_unlock(&dainfo->philos[i].health_mtx);
			return (FAILED);
		}
		pthread_mutex_unlock(&dainfo->philos[i++].health_mtx);
	}
	return (SUCCESSFUL);
}
