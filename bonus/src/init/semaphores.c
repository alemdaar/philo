/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:53:51 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/12 22:41:12 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

static int	smp_name(char *health_str, int i, int len)
{
	char	snb[4];
	char	*snbp;
	int		j;

	snbp = snb;
	snbp = ft_itoa(i);
	j = 0;
	while (j < mystrlen(snbp))
	{
		health_str[len++] = snbp[j++];
		j++;
	}
	health_str[len] = 0;
	return (SUCCESSFUL);
}

static int semaphores4(t_info *dainfo)
{
	int	i;
	int	j;
	int	r;

	dainfo->write = sem_open("/write", O_CREAT, 0644, 1);
	if (dainfo->write == SEM_FAILED)
	{
		j = 0;
		while (j < dainfo->number_of_philosophers)
			sem_close(dainfo->philos[j++].health_smp);
		j = 0;
		while (j < dainfo->number_of_philosophers)
			sem_close(dainfo->philos[j++].meal_smp);
		sem_close(dainfo->forks);
		sem_close(dainfo->death_smp);
		return (free_all(dainfo), output(ERR_ISP, 2), FAILED);
	}
	return (SUCCESSFUL);
}

static int semaphores3(t_info *dainfo)
{
	int	i;
	int	j;
	int	r;
	char meal_str[13] = "/meal_smp";

	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		smp_name(meal_str, i, mystrlen("/meal_smp"));
		printf ("name : %s\n", meal_str);
		dainfo->philos[i].meal_smp = sem_open(meal_str, O_CREAT, 0644, 1);
		if (dainfo->philos[i].meal_smp == SEM_FAILED)
		{
			j = 0;
			while (j < dainfo->number_of_philosophers)
				sem_close(dainfo->philos[j++].health_smp);
			j = 0;
			while (j < i)
				sem_close(dainfo->philos[j++].meal_smp);
			sem_close(dainfo->forks);
			sem_close(dainfo->death_smp);
			return (free_all(dainfo), output(ERR_ISP, 2), FAILED);
		}
		i++;
	}
	r = semaphores4(dainfo);
	return (r);
}

static int	semaphores2(t_info *dainfo)
{
	int	i;
	int	j;
	int	r;
	char health_str[15] = "/health_smp";
	
	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		smp_name(health_str, i, mystrlen("/health_smp"));
		printf ("name : %s\n", health_str);
		dainfo->philos[i].health_smp = sem_open(health_str, O_CREAT, 0644, 1);
		if (dainfo->philos[i].health_smp == SEM_FAILED)
		{
			j = 0;
			while (j < i)
				sem_close(dainfo->philos[j++].health_smp);
			sem_close(dainfo->forks);
			sem_close(dainfo->death_smp);
			return (free_all(dainfo), output(ERR_ISP, 2), FAILED);
		}
		i++;
	}
	r = semaphores3(dainfo);
	return (r);
}

int	semaphores(t_info *dainfo)
{
	int	i;
	int	j;
	int	r;

	dainfo->forks = sem_open("/forks", O_CREAT, 0644, dainfo->number_of_philosophers);
	if (dainfo->forks == SEM_FAILED)
		return (free_all(dainfo), output(ERR_ISP, 2), FAILED);
	dainfo->death_smp = sem_open("/death_mtx", O_CREAT, 0644, 1);
	if (dainfo->forks == SEM_FAILED)
	{
		sem_close(dainfo->forks);
		return (free_all(dainfo), output(ERR_ISP, 2), FAILED);
	}
	dainfo->count_smp = sem_open("/count_mtx", O_CREAT, 0644, 1);
	if (dainfo->forks == SEM_FAILED)
	{
		sem_close(dainfo->forks);
		sem_close(dainfo->death_smp);
		return (free_all(dainfo), output(ERR_ISP, 2), FAILED);
	}
	r = semaphores2(dainfo);
	return (r);
}