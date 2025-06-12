/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <oelhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:54:06 by oelhasso          #+#    #+#             */
/*   Updated: 2025/06/12 22:35:30 by oelhasso         ###   ########.fr       */
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

void	output(char *str, int fd)
{
	write(fd, str, mystrlen(str));
}

void	status(t_philo *philo, char *action, long long date)
{
	sem_wait(philo->dainfo->death_smp);
	if (!philo->dainfo->death)
		printf("%lld %d %s\n", date, philo->id, action);
	sem_post(philo->dainfo->death_smp);
}

static	int	len_count(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len += 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	len = len_count(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len + 1)
		str[i++] = 0;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (len-- && n)
	{
		str[len] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}
