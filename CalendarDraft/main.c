#include<stdio.h>
#include<string.h>
#define MAX_COMMAND_TOKEN_LENGTH 15
char getCommandWord(char command[], int maxLength) {
	char lastCharacter;
	int i;
	for (i = 0; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
	lastCharacter = command[i];
	command[i] = '\0';
	return lastCharacter;
}
void handlePrint() {
	char token[MAX_COMMAND_TOKEN_LENGTH];
	if (getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n') {
		printf("Too many arguments for print command! It must be in the form of print MM/YYYY.\n");
		while (getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n');
		return;
	}
	printf("printing the weeks of month %s\n", token);
	//Your code for printing calendar comes here:
}
void handleCount() {
	char token1[MAX_COMMAND_TOKEN_LENGTH];
	char token2[MAX_COMMAND_TOKEN_LENGTH];
	if (getCommandWord(token1, MAX_COMMAND_TOKEN_LENGTH) == '\n') {
		printf("Too few arguments for count command! It must be in the form of count MM/DD/YYYY mm/dd/yyyy.\n");
		return;
	}
	if (getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) != '\n') {
		printf("Too many arguments for count command! It must be in the form of count MM/DD/YYYY mm/dd/yyyy.\n");
		while (getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) != '\n');
		return;
	}
	printf("counting days from %s to %s\n", token1, token2);
	//Your code for printing calendar comes here:
}
main() {
	char command[MAX_COMMAND_TOKEN_LENGTH];
	char lastCharacter;
	while (1) {
		printf("Please enter a new command...\n");
		lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
		if (!strcmp(command, "quit"))
			break;
		else if (!strcmp(command, "print"))
		{
			if(lastCharacter == '\n')
				printf("Too few arguments for print command! It must be in the form of print MM/YYYY.\n");
			else
				handlePrint();
		}
		else if (!strcmp(command, "count"))
		{
			if (lastCharacter == '\n')
				printf("Too few arguments for count command! It must be in the form of count MM/DD/YYYY mm/dd/yyyy.\n");
			else
				handleCount();
		}
		else {
			printf("invalid command! Your command must start either with quit, or print, or count.\n");
			while (lastCharacter != '\n')
				lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
		}
	}
}
