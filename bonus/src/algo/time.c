/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:36:44 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/12 20:21:00 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

long long	started_timimg(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long long	get_time(t_info *dainfo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (started_timimg() - dainfo->starting_time);
}

int	holding(t_philo *philo, int duration)
{
	long long	now;

	now = get_time(philo->dainfo);
	while ((get_time(philo->dainfo) - now) < duration)
	{
		sem_wait(philo->dainfo->death_smp);
		if (philo->dainfo->death == DEAD)
			return (sem_post(philo->dainfo->death_smp), FAILED);
		sem_post(philo->dainfo->death_smp);
		usleep(500);
	}
	return (SUCCESSFUL);
}
