#include "../../header.h"

void why_exit(int status)
{
	if (status == 0)
		printf ("number is not valid !\n");
	else
		perror ("number is not valid !\n");
	exit(status);
}