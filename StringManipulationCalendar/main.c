#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int days_of_month[] = {
    0,  // used for to make things easier without having to - 1
    31, // jan
    28, // feb
    31, // mar
    30, // apr
    31, // may
    30, // jun
    31, // jul
    31, // aug
    30, // sep
    31, // oct
    30, // nov
    31  // dec
};

char *month_names[] = {
    "Null", //to make things easier without having to -1
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December",
};

int is_leapyear(int yy) {
    //algorithm to determine whether a year is a leap year or not
    // used to add an extra day to February if so
    return (!(yy % 400) || (!(yy % 4) && (yy % 100)));
}

int days_so_far(int mm, int yy) {
    // return days in the year so far up until current month
    int days = 0;
    // start index at 1 to avoid the '0' at index 0
    for (int i = 1; i < mm; i ++) {
        days += days_of_month[i];
        if (i == 2 && is_leapyear(yy)) {
            days += 1;
        }
    }
    return days;
}

int leap_years_so_far(int yy) {
    // algorithm that returns the number of leap years so far up until current year
    // all the times yy evenly divides into 4 or 400
    // minus all the times yy divides into 1000
    return yy/4 + yy/400 - yy/100;
}

int total_days_so_far(int mm, int dd, int yy) {
    //algorithm to calculate total days

    // return total day count from year 0 to date
    int days = 0;

    // days so far in yy up until this mm
    days += days_so_far (mm, yy);
    // at least 365 days each for all previous years
    days += (yy - 1) * 365;
    // and then add days for any previous leap years
    days += leap_years_so_far(yy - 1);
    // and the actual days into the current month
    days += dd;

    return days;
}

void handle_print(int mm, int yy) {
    // function that prints the days of the month
    char *day_header = "Su Mo Tu We Th Fr Sa \n\n";
    //days of the month start at month[1], aka 01 - which represents the days of Jan, 31
    int day_count = days_of_month[mm];
    char *month_header = month_names[mm];
    // total days so far modulus 7 is our week index for display
    int week_index = total_days_so_far(mm, 1, yy) % 7;

    //account for leap years if we're handling feb
    if (mm == 2 && is_leapyear(yy)) {
        day_count += 1;
    }

    // start the calendar display
    printf("\nPRINTING THE WEEKS OF THE MONTH: %d/%d\n", mm, yy);
    printf("\n     %s\n\n", month_header);


    printf(day_header);
    // pad display up to week index
    for (int i = 0; i < week_index; i ++) {
        printf("   ");
    }

    // keep the week index rolling on a modulus
    for (int i = 1; i <= day_count; i++, week_index++ ) {
        // right align the integer
        printf("%2d ", i);
        // newline after every Sa
        if (week_index % 7 == 6) {
            printf("\n\n");
        }
    }
    printf("\n\n");
}

void handle_count(int mm0, int dd0, int yy0,
             int mm1, int dd1, int yy1) {

    printf("\nCOUNTING THE DAYS FROM %d/%d/%d TO %d/%d/%d\n", mm0, dd0, yy0, mm1, dd1, yy1);

    printf("%d days\n\n", total_days_so_far(mm1, dd1, yy1) -
                       total_days_so_far(mm0, dd0, yy0));
}

int main() {
    printf("****CALENDAR PROGRAM****\n\n");
    printf("List of Commands:\n\n");
    printf("* print MM/YYYY\t\t\t prints the days of the month\n");
    printf("* count MM/DD/YYYY mm/dd/yyyy\t counting from a day to another\n");
    printf("* quit\t\t\t\t Exits the program\n\n");
    while (1) {
        char cmd[512], *line = NULL;
        size_t len = 0; //using this for the getline function; needed for the input; it changes with the size of the input

        //prints out string to the standard output (screen)
        fprintf(stdout, "ENTER COMMAND: ");


        //getting input from the keyboard and storing the pointer to the input into the line variable
        //returns the number of characters it read from input
        //the program continues with NULL as input
        if (getline(&line, &len, stdin) < 0) {
            fprintf(stderr, "ERROR! NO LINE");
            return 1;
        }

        memset(cmd, 0, sizeof(cmd)); //setting all characters of cmd to 0
        sscanf(line, "%s", cmd);     //scanning line(the input) for a string(%s) and storing it into cmd

        if (!strcmp(cmd, "quit")){   //compares the cmd & the string which will be commands. It compares character by character
            printf("\nEND OF PROGRAM\n\n");
            break;                   //ends until reaching \0 or null or an unmatched character; if the return value is 0 (equals) then it escapes the while loop
        }

        else if (!strcmp(cmd, "print")) {
            int mm, yy;
            if (sscanf(line+strlen(cmd), "%d/%d", &mm, &yy) == 2) {
                //scanning the line starting right after "print", using the length of cmd as offset
                //for 2 integers (%d) and storing pointers to those integers into mm and yy
                //return value is the amount of successfully scanned variables; if equals 2 then handle_print is called
                handle_print(mm, yy);
            } else {
                fprintf(stderr, "Error! incorrect format: print mm/yyyy\n\n");
            }
        } else if (!strcmp(cmd, "count")) {
            //scanning the line right after "count", using the length of cmd as offset
            //for 6 integers (%d/%d/%d %d/%d/%d) and storing pointers to those integers
            //into corresponding integers
            int dd0, mm0, yy0, dd1, mm1, yy1;
            if (sscanf(line+strlen(cmd), "%d/%d/%d %d/%d/%d",
                       &mm0, &dd0, &yy0, &mm1, &dd1, &yy1) == 6) {
                handle_count(mm0, dd0, yy0, mm1, dd1, yy1);
            } else {
                fprintf(stderr, "Error! incorrect format: count MM/DD/YYYY mm/dd/yyyy\n\n");
            }
        } else {
            fprintf(stderr, "Error! unknown command\n\n");
        }
    }
    return 0;
}
