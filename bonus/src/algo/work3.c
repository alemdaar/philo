/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:16 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/12 22:08:01 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

static int	guarding3(t_info *dainfo)
{
	sem_wait(dainfo->count_smp);
	if (dainfo->count_meal == 1)
		return (SUCCESSFUL);
	return (3);
}

int	guarding2(t_info *dainfo)
{
	int	i;
	int	health;

	i = guarding3(dainfo);
	sem_post(dainfo->count_smp);
	if (i == SUCCESSFUL)
		return (FAILED);
	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		sem_wait(dainfo->philos[i].meal_smp);
		health = (get_time(dainfo) - dainfo->philos[i].last_meal);
		sem_post(dainfo->philos[i].meal_smp);
		sem_wait(dainfo->philos[i].health_smp);
		dainfo->philos[i].health = health;
		if (dainfo->philos[i].health >= dainfo->time_to_die)
		{
			sem_wait(dainfo->death_smp);
			dainfo->death = 1;
			printf ("%lld %d died\n", get_time(dainfo), i + 1);
			sem_post(dainfo->death_smp);
			return (sem_post(dainfo->philos[i].health_smp), 1);
		}
		sem_post(dainfo->philos[i++].health_smp);
	}
	return (SUCCESSFUL);
}
