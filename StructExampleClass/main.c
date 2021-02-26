#include <stdio.h>
#include <stdlib.h>


typedef struct point
{
    int x;
    int y;

}twoDPoint;

twoDPoint makepoint(int x, int y)
{
    twoDPoint temp;
    temp.x = x;
    temp.y = y;

    return temp;

}

int  *makepoint2(int x, int y)
{
    int temp[2];

    temp[0] = x;
    temp[1] = y;

    return temp;
}

int main()
{
              int *coordinates;

    twoDPoint pt1 = { 0, 0 }, pt2 = { 10, 10 }, pt3 = {10, 20};

    pt1 = makepoint(3, 4);
    printf("POINT pt1 IS AT (%d, %d)\n", pt1.x, pt1.y);

    //coordinates = makepoint2(3, 4);
    //printf("Coordinates 0 and 1 are (%d, %d)\n", coordinates[0], coordinates[1]);


    //printf("%d = %d * 2 \n", sizeof(twoDPoint), sizeof(int));

}
