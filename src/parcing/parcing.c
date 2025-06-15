/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:07:27 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/15 21:07:41 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (output(ERR_NNB, 2), 1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (output(ERR_NNB, 2), 1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (output(ERR_NNB, 2), 1);
		i++;
	}
	if (mystrlen(str) > mystrlen("2147483647"))
		return (output(ERR_OVF, 2), 1);
	return (0);
}

int	parcing(int ac, char **av, t_info *dainfo)
{
	int	i;
	int	r;

	i = 1;
	while (i < ac)
	{
		r = is_number(av[i]);
		if (r == FAILED)
			return (FAILED);
		dainfo->tmp_nb[i - 1] = myatoi(av[i]);
		if (dainfo->tmp_nb[i - 1] < 0)
			return (output(ERR_NGT, 2), FAILED);
		if (dainfo->tmp_nb[i - 1] == 0)
			return (output(ERR_NB0, 2), FAILED);
		if (dainfo->tmp_nb[i - 1] > 2147483647)
			return (output(ERR_OVF, 2), FAILED);
		i++;
	}
	if (ac == 5)
		dainfo->number_of_times_each_philosopher_must_eat = -1;
	dainfo->nb_of_inputs = ac - 1;
	return (SUCCESSFUL);
}
