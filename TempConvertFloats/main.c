#include <stdio.h>
#include <stdlib.h>

/*
    Studying C language
    using floats

    This example converts Fahrenheit-Celsius table using floating-points (decimals)

*/

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;          //lower limit of temperature tabel
    upper = 300;        // upper limit
    step = 20;          // step size

    fahr = lower;
    while(fahr <= upper){
        celsius = (5.0/9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}
