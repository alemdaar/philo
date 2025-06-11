/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:12:35 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/10 12:28:02 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	set_philos(t_info *dainfo, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		philo[0][i].id = i + 1;
		if (philo[0][i].id == 1)
			philo[0][i].fork[0] = dainfo->number_of_philosophers - 1;
		else
			philo[0][i].fork[0] = philo[0][i].id - 2;
		philo[0][i].fork[1] = philo[0][i].id - 1;
		philo[0][i].fork[1] = philo[0][i].id - 1;
		philo[0][i].last_meal = -1;
		philo[0][i].health = 0;
		philo[0][i].dainfo = dainfo;
		i++;
	}
	return (SUCCESSFUL);
}

static int	set_info(t_info *dainfo, t_philo **philo)
{
	int	var;
	int	count;

	dainfo->number_of_philosophers = dainfo->tmp_nb[0];
	dainfo->time_to_die = dainfo->tmp_nb[1];
	dainfo->time_to_eat = dainfo->tmp_nb[2];
	dainfo->time_to_sleep = dainfo->tmp_nb[3];
	var = dainfo->tmp_nb[4];
	if (dainfo->nb_of_inputs == 5)
		dainfo->number_of_times_each_philosopher_must_eat = var;
	count = dainfo->number_of_philosophers;
	dainfo->forks = malloc (sizeof(pthread_mutex_t) * count);
	if (!dainfo->forks)
		return (output(ERR_MAF, 2), FAILED);
	philo[0] = malloc (sizeof(t_philo) * dainfo->number_of_philosophers);
	if (!philo[0])
		return (free(dainfo->forks), output(ERR_MAF, 2), FAILED);
	dainfo->count_meal = 0;
	dainfo->death = 0;
	dainfo->trouble = 0;
	dainfo->philos = philo[0];
	return (SUCCESSFUL);
}

int	init(t_info *dainfo, t_philo **philo)
{
	int	r;

	r = set_info(dainfo, philo);
	if (r == FAILED)
		return (FAILED);
	r = set_mutex(dainfo);
	if (r == FAILED)
		return (FAILED);
	r = set_philos(dainfo, philo);
	if (r == FAILED)
		return (FAILED);
	return (SUCCESSFUL);
}
