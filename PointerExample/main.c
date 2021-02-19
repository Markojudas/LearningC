#include <stdio.h>
#include <stdlib.h>

float f(int *arr){
    //returns the average of numbers in a
    float returnValue = 0;

    for(int i = 0; i < 10; i++){
        returnValue += arr[i];
    }
    return returnValue / 10;

}

int strlen2(char *s){

    char *p = s;

    //printf("p before loop is: %ld\n", p);

    while (*p != '\0'){
        p++;
    }
    /*
    printf("p is: %ld\n", p);
    printf("s is: %ld\n", s);
    printf("p - s is: %ld\n", p-s);
    */
    return p - s;
}

int main()
{
    int a[10];
    float b;
    b = f(a);
    int i;

    //initializing the array
    for(i = 0; i <10; i++){
        a[i] = i;
    }
    b = f(a);
    //passing array a
    //the name of the array is also the address of the first cell of the array a[0]
    printf("%.1f\n", b);

    char *x = "HELLO";


    printf("\nThe length of %s is: %d\n", x, strlen2(x));

    //strlen2("WORLD");

}
