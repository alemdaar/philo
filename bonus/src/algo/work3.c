/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:16 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/13 14:43:47 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

int	guarding2(t_philo *philo)
{
	int	i;
	int	health;

	if (philo->count_meal == 1)
		return (FAILED);
	i = 0;
	while (i < philo->dainfo->number_of_philosophers)
	{
		sem_wait(philo->meal_smp);
		health = (get_time(philo->dainfo) - philo->last_meal);
		sem_post(philo->meal_smp);
		sem_wait(philo->health_smp);
		philo->health = health;
		if (philo->health >= philo->dainfo->time_to_die)
		{
			sem_wait(dainfo->death_smp);
			printf ("%lld %d died\n", get_time(dainfo), i + 1);
			sem_post(dainfo->death_smp);
			return (sem_post(dainfo->philos[i].health_smp), 1);
		}
		sem_post(dainfo->philos[i++].health_smp);
	}
	return (SUCCESSFUL);
}
