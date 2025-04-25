#include <unistd.h>
#include <stdio.h>

int main ()
{
    char *str1;
    char str2[5];
    str2[0] = 'a';
    str2[1] = 'a';
    str2[2] = 0;
    str1 = str2;

    printf ("%s\n", str1);
}
