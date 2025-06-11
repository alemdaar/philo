/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:57:33 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/11 21:36:09 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

void clean_smp(t_info *dainfo)
{
	int	i;

	sem_close(dainfo->count_smp);
	sem_close(dainfo->death_smp);
	sem_close(dainfo->forks);
	sem_close(dainfo->write);
	sem_unlink("/count_smp");
	sem_unlink("/death_smp");
	sem_unlink("/forks");
	sem_unlink("/write");
	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		sem_close(dainfo->philos[i].health_smp);
		sem_close(dainfo->philos[i].meal_smp);
		sem_unlink("/health_smp");
		sem_unlink("/meal_smp");
		i++;
	}
	return ;
}

void	free_all(t_info *dainfo)
{
	free(dainfo->forks);
	free(dainfo->philos);
	return ;
}

void    clean(t_info *dainfo)
{
    clean_smp(&dainfo);
    free_all(dainfo);
}
