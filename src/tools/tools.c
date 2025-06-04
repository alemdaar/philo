#include "../../header.h"

int mystrlen(char *str)
{
    if (!str)
        return 0;
    int i = 0;
    while (str[i])
        i++;
    return i;
}

int long long myatoi(char *str)
{
    int i = 0;
    int sign = 1;
    int long long nb = 0;
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
	pthread_mutex_lock(&philo->dainfo->death_mtx);
	if (!philo->dainfo->death)
		printf("%lld %d %s\n", date, philo->id, action);
	pthread_mutex_unlock(&philo->dainfo->death_mtx);
}
