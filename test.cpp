#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int* s = (int *) calloc (5, sizeof(int));

    for (int i = 0; i < 5; ++i)
        s[i] = 25 - 4 * i;

    s = (int *) realloc (s, 10);

    s[6] = 1000;

    printf ("%d\n", s[6]);
}
