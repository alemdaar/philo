#include "../../header.h"

int is_number(char *str)
{
    int i;
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!str[i])
        return 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

void set_up(char av, t_info *dainfo)
{

}

void    check_input(int ac, char **av, t_info *dainfo)
{
	int i;
	int r;
	i = 1;
	int nb[ac - 1];
	while (i < ac - 1)
	{
		r = is_number(av[i]);
		if (r == 0)
		    why_exit("the inpit is not a number\n", 1);
		nb[i] = myatoia(av[i]);
		if (nb[i] == 0 && i != 5)
		    why_exit("one of the inputs is 0\n", 1);
		i++;
	}
	if (ac == 5)
		dainfo->number_of_times_each_philosopher_must_eat = -1;
	dainfo->nb_of_inputs = ac - 1;
	set_up(av, dainfo, nb);
	return;
}

void	parcing(int ac, char **av, t_info *dainfo)
{
	check_input(av, ac, dainfo);
}
