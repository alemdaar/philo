/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:53:51 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/14 22:42:51 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

int	smp_name(char **str, int i, int len)
{
	char	*snbp;
	int		j;

	snbp = ft_itoa(i);
	j = 0;
	while (j < mystrlen(snbp))
	{
		str[0][len] = snbp[j];
		j++;
		len++;
	}
	str[0][len] = 0;
	free(snbp);
	return (SUCCESSFUL);
}

static int semaphores4(t_info *dainfo)
{
	int	i;
	int	j;
	int	r;
	char count_str[14] = "/count_smp";
	char *tmp;

	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		tmp = count_str;
		smp_name(&tmp, i, mystrlen("/count_smp"));
		printf ("str : %s\n", count_str);
		dainfo->philos[i].count_smp = sem_open(count_str, O_CREAT, 0644, 1);
		if (dainfo->philos[i].count_smp == SEM_FAILED)
			return (clean(dainfo), output(ERR_ISP, 2), FAILED);
		i++;
	}
	return (SUCCESSFUL);
}

static int semaphores3(t_info *dainfo)
{
	int	i;
	int	j;
	int	r;
	char meal_str[13] = "/meal_smp";
	char *tmp;

	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		tmp = meal_str;
		smp_name(&tmp, i, mystrlen("/meal_smp"));
		printf ("str : %s\n", meal_str);
		dainfo->philos[i].meal_smp = sem_open(meal_str, O_CREAT, 0644, 1);
		if (dainfo->philos[i].meal_smp == SEM_FAILED)
			return (clean(dainfo), output(ERR_ISP, 2), FAILED);
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
	char *health_str;
	char health_str2[32] = "/health_smp";
	
	i = 0;
	while (i < dainfo->number_of_philosophers)
	{
		health_str = health_str2;

		smp_name(&health_str, i, mystrlen("/health_smp"));

		printf ("str : %s\n", health_str);
		write (1, "a\n", 2);

		dainfo->philos[i].health_smp = sem_open(health_str, O_CREAT , 0644, 1);


		if (dainfo->philos[i].health_smp == SEM_FAILED)
			return (clean(dainfo), output(ERR_ISP, 2), FAILED);

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
	dainfo->write = sem_open("/write", O_CREAT, 0644, 1);
	if (dainfo->forks == SEM_FAILED)
		return (clean(dainfo), output(ERR_ISP, 2), FAILED);
	r = semaphores2(dainfo);
	return (r);
}
