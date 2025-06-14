/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:09:09 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/14 20:00:49 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

int	main(int ac, char **av)
{
	t_info	dainfo;
	t_philo	*philo;
	int		r;

	if (ac != 5 && ac != 6)
		return (output("number of args is != valid\n", 2), 1);
	clean_smp(&dainfo);
	r = parcing(ac, av, &dainfo);
	if (r == FAILED)
		return (1);
	r = init(&dainfo, &philo);
	if (r == FAILED)
		return (1);
	if (dainfo.number_of_philosophers == 1)
		r = one_philo(philo, &dainfo);
	else
		r = algo(&dainfo);
	clean(&dainfo);
	if (r == ERROR)
		return (1);
	return (0);
}
