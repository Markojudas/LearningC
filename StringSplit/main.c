#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_first_weekday(int year)
{
    int day;

    day = (((year - 1)* 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year) / 400) + 1) % 7;
    //Sunday is 0
    //Saturday is 6

    return day;
}


int main()
{
    char str[7];
    //char month[20], year[20], dtm[100];

    int i;

    printf("ENTER MM/YYYY: ");

    for(i = 0; i < 7; i++){
       scanf("%c", &str[i]);
    }


    //printf("size of str is: %ld\n\n", strlen(str));
    //printf("Size of Month before anything is: %ld\n", strlen(month));

    int init_size = strlen(str);
    char delim[] = "/";

    char *ptr = strtok(str, delim);

    char month[2];

    //printf("Size of month before loop: %ld\n", strlen(month));

    for(i = 0; i < ; i++){
        month[i] = ptr[i];
        printf("The INDEX %d of Month: %c\n", i, month[i]);
    }

    //printf("Size of Month after is: %ld\n", strlen(month));

    char x[4];
    //printf("Size of X before loop is: %ld\n", strlen(x));

    for(i = 0; i < 7; i++){
        printf("THE INDEX %d: %c\n", i, ptr[i]);
    }

    for(i = 3; i <= 6; i++){
        x[i- 3] = ptr[i];
    }
    //printf("size of X after loop is: %ld\n", strlen(x));

    char year[4];
    //printf("size of year before loop: %ld\n", strlen(year));
    for(i = 0; i < 4; i++){
        year[i] = x[i];
    }
    //printf("the size of year after loop is: %ld\n", strlen(year));

    /*
    int monthNumber = atoi(month);

    printf("Month Number is: %d \n", monthNumber);

    printf("size of the year is: %ld\n", strlen(year));
    printf("size of the month is: %ld\n", strlen(month));

    int yearNumber = atoi(year);

    printf("Year Number is: %d \n", yearNumber);

    char yearString[] = " ";

    for(i = 0; i < 4; i++){
        strcat(yearString, string);
    }



    for(i = 0; i < 4; i++){
        printf("the year index %d: %c\n", i, year[i]);
    }

    int monthNumber = atoi(month);

    printf("month is %d\n", monthNumber);

    int yearNumber = atoi(year);

    printf("year is %d\n", yearNumber);


    while (ptr != NULL){
        printf("%s\n", ptr);
        ptr = strtok(NULL, delim);
    }


    int year, month, day, daysInMonth, weekDay, startingDay;

    year = atoi(ptr[1]);
    month = atoi(ptr[0]);

    char *months[]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int monthDay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        //leap year
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        monthDay[1] = 29;
    }

    startingDay = get_first_weekday(year);

    daysInMonth = monthDay[month];
    printf("\n\n----------------%s------------------\n", months[month]);
    printf("\n  Sun  Mon  Tue  Wed  Thurs  Fri  Sat\n\n");

    for(weekDay = 0; weekDay < startingDay; weekDay++){
        printf("     ");
    }
    for(day = 1; day <= daysInMonth; day++){
        printf("%5d", day);

        if(++weekDay > 6){
            printf("\n\n");
            weekDay = 0;
        }
        startingDay = weekDay;
    }
    printf("\n");
    */
}
