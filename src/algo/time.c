/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:36:44 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/04 22:36:45 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

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
		pthread_mutex_lock(&philo->dainfo->death_mtx);
		if (philo->dainfo->death IS DEAD)
			return (pthread_mutex_unlock(&philo->dainfo->death_mtx), FAILED);
		pthread_mutex_unlock(&philo->dainfo->death_mtx);
		usleep(500);
	}
	return (SUCCESSFUL);
}
