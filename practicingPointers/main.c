#include <stdio.h>

int main()
{
    int x = 1, z[10];
    int *ip;

    ip = &x;

    printf("printing the value of x: %d\n", x);
    printf("ip holds the address of x, and whatever it is stored in x = %d\n", *ip);

    *ip = *ip + 10;  //adding 10 to whatever ip points to; ip points to x and its content (1)

    printf("ip is pointing to x and the new value of x is: %d\n", *ip);
    printf("x = %d\n", x);

    int y = 0;

    y = *ip + 1;  //adding 1 to whatever ip points to, x; x = 11, so y is now 12

    printf("y = %d\n", y);

    *ip += 1; //increments what ip points to (currently poitning at x which has been incremented to 11 on line 20; so after this x = 12)

    printf("IP NOW POINTS TO: %d\n", *ip);

    //creating another pointer

    int *iq;

    iq = ip;  //this copies whatever ip is pointing at. iq now points also there

    printf("iq is pointing to: %d\n", *iq);  //x = 12; *iq holds the address of x, and will display the contents, 12

    //doing some arithmetic with the new pointer

    *iq = *iq + 2;  //since iq is now also pointing at x which is 12, plus 2 x is now 14

    printf("X is now: %d\n", x);
    printf("*iq is also : %d\n", *iq);  //should be also 14

    //storing the size of the array in a variable called len
    int len = sizeof(z)/sizeof(z[0]);

    printf("printing the size of the array\n");
    printf("int array z is of size: %d\n", len);

    //storing value to the int array z
    for(int i = 0; i < len; i++){
        z[i] = i + 5;  // array is now {5, 6, 7, 8, 9, 10, 11, 12, 13, 14}
    }

    //ip is now pointing at index 0 of z, which is 5
    ip = &z[0];

    //printing the pointer ip
    printf("IP IS POINTING AT INDEX 0 of ARRAY Z, WHICH HOLDS THE FOLLOWING VALUE: %d\n", *ip);

    //what about index 6? which should be 11
    int *f;

    f = ip +6;

    printf("f is pointing at index 6 and the contents are:  %d\n", *f);


   //what about index 7?  this time with a regular int variable

    int d, s;

    d = *ip + 7;   //this gets the content of index 7

    s = d + 5;     //this adds the content of index 7, stored in d and adds 5 = 12 + 5 = 17

    printf("the value of d is: %d\n", d);
    printf("the value of s is: %d\n", s);

    int g;

    g = (*ip + 8) + 2;   // 13 + 2?

    printf("The value of g is: %d\n", g);

}

