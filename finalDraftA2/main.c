/*
    Assignment 2: Gregorian Calendar
    Programmer: Jose R Hernnadez
    Course: Systems Programming - COP4338 - U01 - 1211
    Semester: Spring 2021
    Instructor: Kianoosh G. Boroojeni, Ph.D.

    This program will print the weeks of a given month and year
    It will also calculate the days between two given dates
*/


#include<stdio.h>
#include<string.h>
#define MAX_COMMAND_TOKEN_LENGTH 15


int days_of_month[] = {
    0,  // used to make things easier without having to +- 1
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
    "Invalid Month", //to make things easier without having to +- 1
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
    //used to add an extra day to February if so

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

void printWeeksOfMonth(int mm, int yy) {
    // function that prints the days of the month

    char *day_header = "Su Mo Tu We Th Fr Sa \n";
    char *month_header = month_names[mm];

    //days of the month start at month[1], aka 01 - which represents the days of Jan, 31
    //identifies how many days in a given month
    int day_count = days_of_month[mm];

    // total days so far modulus 7 is our week index for display
    int week_index = total_days_so_far(mm, 1, yy) % 7;

    //account for leap years if we're handling feb
    if (mm == 2 && is_leapyear(yy)) {
        day_count += 1;
    }

    // start the calendar display
    printf("      %s\n", month_header);

    printf(day_header);

    //pad display up to week index
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
    printf("\n\n");
}

void countDays(int mm0, int dd0, int yy0,
             int mm1, int dd1, int yy1) {

    /*
        prints the difference between two dates
        a negative result means the difference between a future date vs an earlier one
        abs() could be use to handle negatives
    */

    printf("%d days\n\n", total_days_so_far(mm1, dd1, yy1) -
                       total_days_so_far(mm0, dd0, yy0));
}


char getCommandWord(char command[], int maxLength) {
    //function to tokenize the INPUT
    //finding the lastCharacter which could be either whitespace or a new line

	char lastCharacter;
	int i;

	//empty for loop that stops until it is false, meaning a whitespace or a new line was encountered
	//or if it reaches the end of the input
	for (i = 0; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
	lastCharacter = command[i];
	command[i] = '\0';
	return lastCharacter;
}

void handlePrint() {
    /*
    function to tokenize the input with mm/yyyy
    Using the getCommandWord() function continuing getchar() until a lastCharacter is identified (whitespace or new line)
    Using sscanf() function to read/scan the token for the format %d/%d and storing a pointer for the found integers into the mm & yy variables
    sscanf() function returns the number of sucessfully scanned items (integers in this case)
    Checks whether a valid month is passed (1 - 12)
    Then calling the printWeeksOfMonth() function defined above
    */

	char token[MAX_COMMAND_TOKEN_LENGTH];
	int mm, yy;
	if (getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n') {
		printf("\nERROR! too many arguments for print command! It must be in the form of print MM/YYYY.\n\n");
		while (getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n');
		return;
	}else if((sscanf(token, "%d/%d", &mm, &yy)) == 2){
	    if(mm < 1 || mm > 12){
	        printf("\n%s ERROR\n\n", month_names[0]);
	        return;
	    }else{
	        printf("\nPrinting the weeks of month: %s\n\n", token);
	        printWeeksOfMonth(mm, yy);
	    }
	}else{
	    printf("\nERROR IN INPUT\n\n");
	}
}

void handleCount() {
    /*
        function to tokenize the input with MM/DD/YYYY mm/dd/yyyy; two dates - creating 2 tokens
        Using the getCommandWord() function for each token continuing getchar() until a lastCharacter is found
        Token1 lastCharacter is a whitespace while token2 lastCharacter is a new line
        Using sscanf() to scan through token1 and token2 for the format %d/%d/%d and storing a pointer for the found integers into
        their corresponding mm, dd, yyyy variables
        Checks whether a valid month and day (1 -12 and 1 - 31) is passed
        Then calling the countDays() function defined above
    */

	char token1[MAX_COMMAND_TOKEN_LENGTH];
	char token2[MAX_COMMAND_TOKEN_LENGTH];
	int dd0, mm0, yy0, dd1, mm1, yy1;

	if (getCommandWord(token1, MAX_COMMAND_TOKEN_LENGTH) == '\n') {
		printf("\nERROR! too few arguments for count command! It must be in the form of count MM/DD/YYYY mm/dd/yyyy.\n\n");
		return;
	}
	if (getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) != '\n') {
		printf("\nERROR! too many arguments for count command! It must be in the form of count MM/DD/YYYY mm/dd/yyyy.\n\n");
		while (getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) != '\n');
		return;
	}

    if((sscanf(token1, "%d/%d/%d", &mm0, &dd0, &yy0) == 3) && (sscanf(token2, "%d/%d/%d", &mm1, &dd1, &yy1) == 3)){

        if(mm0 < 1 || mm0 > 12 || mm1 < 1 || mm1 > 12 || dd0 < 1 || dd0 > 31 || dd1 < 1 || dd1 > 31){
            printf("\nERROR! invalid input\n\n");
            return;
        }else{
            printf("\nCounting days from %s to %s\n", token1, token2);
            countDays(mm0, dd0, yy0, mm1, dd1, yy1);
        }
    }else{
        printf("\nERROR IN INPUT\n");
    }
}

int main() {
	char command[MAX_COMMAND_TOKEN_LENGTH];
	char lastCharacter;

	//This is purely aesthetics
	printf("****CALENDAR PROGRAM****\n\n");
    printf("List of Commands:\n\n");
    printf("* print MM/YYYY\t\t\t prints the days of the month\n");
    printf("* count MM/DD/YYYY mm/dd/yyyy\t counting from a day to another\n");
    printf("* quit\t\t\t\t Exits the program\n\n");

    /*
        Starts the loop
        Calls the getCommandWord() function to get input from the user (stdin)
        Indentifying the lastCharacter will tokenize the command word
        Expecting quit, print, count as the Commands
        Using the strcmp() function to compare tokenized command vs the input
        this function compares the content of the string, one character at a time
        until it reaches the end of the string \0 or different character
        it returns the difference of those characters; returns 0 if they are equal
        ! is equivalent to == 0
    */

	while (1) {
		printf("Please enter a new command: ");
		lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);

		if (!strcmp(command, "quit")){
		    printf("\nEnd of program!\n");
		    break;
		}
		else if (!strcmp(command, "print"))
		{
			if(lastCharacter == '\n')
				printf("\nERROR! too few arguments for print command! It must be in the form of print MM/YYYY.\n\n");
			else
				handlePrint();
		}
		else if (!strcmp(command, "count"))
		{
			if (lastCharacter == '\n')
				printf("\nERROR! too few arguments for count command! It must be in the form of count MM/DD/YYYY mm/dd/yyyy.\n\n");
			else
				handleCount();
		}
		else {
			printf("\nERROR! invalid command! Your command must start either with quit, or print, or count.\n\n");
			while (lastCharacter != '\n')
				lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
		}
	}
}
