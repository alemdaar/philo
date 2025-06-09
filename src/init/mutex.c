/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:28:33 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/09 22:05:28 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	set_mutex4(t_info *dainfo)
{
	int	r;
	int	j;

	r = pthread_mutex_init(&dainfo->count_mtx, NULL);
	if (r != SUCCESSFUL)
	{
		pthread_mutex_destroy(&dainfo->death_mtx);
		j = 0;
		while (j < dainfo->number_of_philosophers)
			pthread_mutex_destroy(&dainfo->philos[j++].health_mtx);
		j = 0;
		while (j < dainfo->number_of_philosophers)
			pthread_mutex_destroy(&dainfo->forks[j++]);
		j = 0;
		while (j < dainfo->number_of_philosophers)
			pthread_mutex_destroy(&dainfo->philos[j++].meal_mtx);
		return (free_all(dainfo), output(ERR_INM, 2), FAILED);
	}
	return (r);
}

static int	set_mutex3(t_info *dainfo)
{
	int	r;
	int	i;
	int	j;

	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		r = pthread_mutex_init(&dainfo->forks[i++], NULL);
		if (r != SUCCESSFUL)
		{
			pthread_mutex_destroy(&dainfo->death_mtx);
			j = 0;
			while (j < dainfo->number_of_philosophers)
				pthread_mutex_destroy(&dainfo->philos[j++].health_mtx);
			j = 0;
			while (j < dainfo->number_of_philosophers)
				pthread_mutex_destroy(&dainfo->philos[j++].meal_mtx);
			j = 0;
			while (j < i - 1)
				pthread_mutex_destroy(&dainfo->forks[j++]);
			return (free_all(dainfo), output(ERR_INM, 2), FAILED);
		}
	}
	r = set_mutex4(dainfo);
	return (r);
}

static int	set_mutex2(t_info *dainfo)
{
	int	i;
	int	r;
	int	j;

	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		r = pthread_mutex_init(&dainfo->philos[i++].meal_mtx, NULL);
		if (r != SUCCESSFUL)
		{
			pthread_mutex_destroy(&dainfo->death_mtx);
			j = 0;
			while (j < dainfo->number_of_philosophers)
				pthread_mutex_destroy(&dainfo->philos[j++].health_mtx);
			j = 0;
			while (j < i - 1)
				pthread_mutex_destroy(&dainfo->philos[j++].meal_mtx);
			return (free_all(dainfo), output(ERR_INM, 2), FAILED);
		}
	}
	r = set_mutex3(dainfo);
	return (r);
}

int	set_mutex(t_info *dainfo)
{
	int	i;
	int	r;
	int	j;

	r = pthread_mutex_init(&dainfo->death_mtx, NULL);
	if (r != SUCCESSFUL)
		return (free_all(dainfo), output(ERR_INM, 2), FAILED);
	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		r = pthread_mutex_init(&dainfo->philos[i++].health_mtx, NULL);
		if (r != SUCCESSFUL)
		{
			pthread_mutex_destroy(&dainfo->death_mtx);
			j = 0;
			while (j < i - 1)
				pthread_mutex_destroy(&dainfo->philos[j++].health_mtx);
			return (free_all(dainfo), output(ERR_INM, 2), FAILED);
		}
	}
	r = set_mutex2(dainfo);
	return (r);
}
