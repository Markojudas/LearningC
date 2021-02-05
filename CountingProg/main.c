#include <stdio.h>
#include <stdlib.h>

int main()
{
    long nc; //number characters

    nc = 0;

    while(getchar() != EOF){
        ++nc;
    }
    printf("%1d\n", nc);
}
