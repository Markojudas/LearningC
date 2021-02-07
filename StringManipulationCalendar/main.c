#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int days_of_month[] = {
    0,  // index pad for convenience (don't have to mm-1 etc.)
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

int
is_leapyear(int yy) {
    // use this to determine if a year gets an extra day for feb
    return (!(yy % 400) || (!(yy % 4) && (yy % 100)));
}

int
days_so_far(int mm, int yy) {
    // return days in the year so far up until mm
    int days = 0;
    // start index at 1 because of our mm index pad
    for (int i = 1; i < mm; i ++) {
        days += days_of_month[i];
        if (i == 2 && is_leapyear(yy)) {
            days += 1;
        }
    }
    return days;
}

int
leap_years_so_far(int yy) {
    // return the number of leap years so far up until yy
    // all the times yy evenly divides into 4 or 400
    // minus all the times yy divides into 1000
    return yy/4 + yy/400 - yy/100;
}

int
total_days_so_far(int dd, int mm, int yy) {
    // return total day count from year 0 to date
    int days = 0;

    // days so far in yy up until this mm
    days += days_so_far(mm, yy);
    // at least 365 days each for all previous years
    days += (yy - 1) * 365;
    // and then add days for any previous leap years
    days += leap_years_so_far(yy - 1);
    // and the actual offset into the current month
    days += dd;

    return days;
}

void
handle_print(int mm, int yy) {
    // handle print logic here
    char *day_header = "Su Mo Tu We Th Fr Sa \n";
    // index pad, no need to adjust index for mm
    int day_count = days_of_month[mm];
    // total days so far modulus 7 is our week index for display
    int week_index = total_days_so_far(1, mm, yy) % 7;

    // account for leap years if we're handling feb
    if (mm == 2 && is_leapyear(yy)) {
        day_count += 1;
    }
    // start the calendar display
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
            printf("\n");
        }
    }
    // clean up
    printf("\n");
}

void
handle_count(int dd0, int mm0, int yy0,
             int dd1, int mm1, int yy1) {
    // get the absolute value so we don't care about ordering
    printf("%d\n", abs(total_days_so_far(dd1, mm1, yy1) -
                       total_days_so_far(dd0, mm0, yy0)));
}

int
main() {
    while (1) {
        char cmd[512], *line = NULL;
        size_t len = 0;

        fprintf(stdout, "Cmd: ");

        // getline on NULL and 0 will alloc
        if (getline(&line, &len, stdin) < 0) {
            fprintf(stderr, "Fatal: could not get line\n");
            return 1;
        };

        memset(cmd, 0, sizeof(cmd));
        sscanf(line, "%s", cmd);

        if (!strcmp(cmd, "print")) {
            int mm, yy;
            if (sscanf(line+strlen(cmd), "%d/%d", &mm, &yy) == 2) {
                handle_print(mm, yy);
            } else {
                fprintf(stderr, "Error: could not parse input\n");
            }
        } else if (!strcmp(cmd, "count")) {
            int dd0, mm0, yy0, dd1, mm1, yy1;
            if (sscanf(line+strlen(cmd), "%d/%d/%d %d/%d/%d",
                       &dd0, &mm0, &yy0, &dd1, &mm1, &yy1) == 6) {
                handle_count(dd0, mm0, yy0, dd1, mm1, yy1);
            } else {
                fprintf(stderr, "Error: could not parse input\n");
            }
        } else {
            fprintf(stderr, "Error: could not parse input\n");
        }

        // prevent memory leak
        if (line)
            free(line);
    }

    return 0;
}
