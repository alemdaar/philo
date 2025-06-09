/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:14:21 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/09 20:18:45 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	free_all(t_info *dainfo)
{
	free(dainfo->forks);
	free(dainfo->philos);
	return ;
}

void	clean(t_info *dainfo)
{
	int	i;

	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		pthread_mutex_destroy(&dainfo->philos[i].health_mtx);
		pthread_mutex_destroy(&dainfo->philos[i].meal_mtx);
		pthread_mutex_destroy(&dainfo->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&dainfo->death_mtx);
	pthread_mutex_destroy(&dainfo->count_mtx);
	free_all(dainfo);
	return ;
}
