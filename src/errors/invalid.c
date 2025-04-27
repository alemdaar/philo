#include "../../header.h"

void why_exit(char *str, int status)
{
	if (status == 0)
		write(1, str, mystrlen(str));
	else
		write(2, str, mystrlen(str));
	exit(status);
}