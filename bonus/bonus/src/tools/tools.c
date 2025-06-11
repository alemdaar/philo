/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:54:06 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/11 20:56:46 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

int	mystrlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

long long	myatoi(char *str)
{
	int			i;
	int			sign;
	long long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
		nb = (nb * 10) + (str[i++] - 48);
	nb *= sign;
	return (nb);
}

// void	output(char *str, int fd)
// {
// 	write(fd, str, mystrlen(str));
// }

// void	status(t_philo *philo, char *action, long long date)
// {
// 	pthread_mutex_lock(&philo->dainfo->death_mtx);
// 	if (!philo->dainfo->death)
// 		printf("%lld %d %s\n", date, philo->id, action);
// 	pthread_mutex_unlock(&philo->dainfo->death_mtx);
// }
