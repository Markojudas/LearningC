#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array[] = {0,1};

    int size = sizeof(array)/sizeof(array[0]);

    printf("size of array: %d\n", size);
}
