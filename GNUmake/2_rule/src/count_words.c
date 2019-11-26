#include <stdio.h>

int main()
{
    int i, counts[4] = { 0 };
    counter(counts);
    for (i = 0; i < 4; i++) {
        printf("counts[%d]=%d\n", i + 1, counts[i]);
    }
    return 0;
}
