#include <stdio.h>
#include <stdlib.h>

/*
    Copy input to output
    Displaying user input; character input
    There is no STRING class but there is char
    this prints the input 1 character at a type
*/


int main()
{
    int c;

    c = getchar(); //to get the next input character from the standard input text stream

    /*
    while (c != EOF){
            //EOF stands for End Of File; pretty much reads if there are more characters.
        putchar(c); //to print a single character to the standard output text stream;
        c = getchar();
    }
    */

    //other while loops

    while ((c = getchar()) != EOF){
        putchar(c);
    }

}
