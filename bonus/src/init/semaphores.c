/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:53:51 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/11 16:37:02 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

int	semaphores(t_info *dainfo)
{
	int	i;

	dainfo->forks = sem_open("/forks", O_CREAT, 0644, dainfo->number_of_philosophers);
	dainfo->death_mtx = sem_open("/death_mtx", O_CREAT, 0644, 1);
	dainfo->count_mtx = sem_open("/count_mtx", O_CREAT, 0644, 1);
	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		dainfo->philos[i].health_smp = sem_open("/health_smp", O_CREAT, 0644, 1);
		i++;
	}
	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		dainfo->philos[i].meal_smp = sem_open("/meal_smp", O_CREAT, 0644, 1);
		i++;
	}
	return (SUCCESSFUL);
}