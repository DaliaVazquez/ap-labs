#include <stdio.h>


void swap(int *px, int *py)
{
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

int main() {

    int x = 1, y = 2;

    printf("Before Swap: x = %i, y = %i\n", x, y);

    swap(&x,&y);

    printf("After Swap: x = %i, y = %i\n", x, y);

    return 0;
}