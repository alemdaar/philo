#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void	my_putnbr(suseconds_t n)
{
	int tmp;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write (1, "-2147483648", 11);
			return ;
		}
		write(1, "-", 1);
		n = -n;
	}
	if (n / 10)
	{
		my_putnbr(n / 10);
		my_putnbr(n % 10);
	}
	else
	{
		tmp = 48 + n;
		write(1, &tmp, 1);
	}
}

int main()
{
    my_putnbr(123);
    printf ("\n");

    my_putnbr(-123);
    printf ("\n");

    my_putnbr(0);
    printf ("\n");

    my_putnbr(-0);
    printf ("\n");

    my_putnbr(+0);
    printf ("\n");

    my_putnbr(+123);
    printf ("\n");

    my_putnbr(5);
    printf ("\n");

    my_putnbr(-3);
    printf ("\n");

    my_putnbr(-9875);
    printf ("\n");

    my_putnbr(+9875);
    printf ("\n");

    return 0;
}
