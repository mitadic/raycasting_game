#include <stdio.h>
#include <limits.h>

int main(void)
{
    float   i;
    __uint64_t      incr;
    __uint64_t      max;

    i = 0.0;
    incr = 0;
    max = 2147483647;
    max += 2147483647;
    max += 2147483647;
    max += 2147483647;
    max += 2147483647;
    while (++incr <  max)
        printf("float is: %f\n", i + incr);
    printf("\ndone\n");
}