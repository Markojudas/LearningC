#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nc; //number characters

    nc = 0;

    while(getchar() != '\n'){
        ++nc;
    }
    printf("NUMBER OF CHARACTERS: ");
    printf("%1d\n", nc);
}
