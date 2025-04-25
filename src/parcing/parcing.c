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
void    check_input(int ac, char **av, t_info *info)
{
    int i;
    int r;
    i = 1;
    int nb[ac - 1];
    while (i < ac)
    {
        r = is_number(av[i]);
        if (r == 0)
            why_exit("the inpit is not a number\n", 1);
        nb[i] = myatoia(av[i]);
        if (nb[i] == 0)
            why_exit("one of the inputs is 0\n", 1);
        i++;
    }
    if (nb[0] > 200)
        why_exit("the number of philos is bigger than 200\n", 1);
    
}

int parcing(int ac, char **av, t_info *dainfo)
{
    check_input(av, ac);
}
