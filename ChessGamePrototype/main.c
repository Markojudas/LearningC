#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CELLS_ROW 8
#define MAX_CELLS_COLUMN 8
#define MAX_COMMAND_TOKEN_LENGTH 15

static int chessBoard[8][8] = {
    {-4, -2, -3, -5, -6, -3, -2, -4}, //chessBoard[0][0-7]
    {-1, -1, -1, -1, -1, -1, -1, -1}, //chessBoard[1][0-7]
    {0, 0, 0, 0, 0, 0, 0, 0},         //chessBoard[2][0-7]
    {0, 0, 0, 0, 0, 0, 0, 0},         //chessBoard[3][0-7]
    {0, 0, 0, 0, 0, 0, 0, 0},         //chessBoard[4][0-7]
    {0, 0, 0, 0, 0, 0, 0, 0},         //chessBoard[5][0-7]
    {1, 1, 1, 1, 1, 1, 1, 1},         //chessBoard[6][0-7]
    {4, 2, 3, 5, 6, 3, 2, 4}          //chessBoard[7][0-7]
};

void printBoard(){
    char *header = "  a |  b |  c |  d |  e |  f |  g |  h |\n";

    //starting to print the board
    printf("BOARD* ");

    printf("%s", header);
    printf("     ******************************************\n");

    for(int x = 0; x < MAX_CELLS_COLUMN; x++){
        printf("%d    *  ", (8 - x));
        for(int y = 0; y < MAX_CELLS_COLUMN; y++){
            if(chessBoard[x][y] != 0){
                printf("%2d |", chessBoard[x][y]);
            }else{
                printf(" 0 |");
            }
            printf(" ");
        }
        printf("\n");
    }
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

void handleMove(){
    char token[MAX_COMMAND_TOKEN_LENGTH];
    //char token[MAX_COMMAND_TOKEN_LENGTH];
    if(getCommandWord(token, MAX_CELLS_COLUMN) != '\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n');
        return;
    }else{
        printf("\nPENDING IMPLEMENTATION OF MOVE\n\n");
        return; //placeholder
    }
}

void handleCapture(){
    char token[MAX_COMMAND_TOKEN_LENGTH];
    //char token[MAX_COMMAND_TOKEN_LENGTH];
    if(getCommandWord(token, MAX_CELLS_COLUMN) != '\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n');
        return;
    }else{
        printf("\nPENDING IMPLEMENTATION OF CAPTURE\n\n");
        return; //placeholder
    }
}

int main()
{
    char cmd[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;

    printf("*********************************************\n");
    printf("\t\tCHESS GAME!!!\n");
    printf("*********************************************\n\n");
    printf("Commands:\n");
    printf("mv <AB> <ab>");    printf("\t\tmoves AB to position ab\n");
    printf("cp <AB> <ab>");    printf("\t\tAB captures ab\n");
    printf("show"); printf("\t\t\tprints out board\n");
    printf("quit"); printf("\t\t\tquits the game\n\n");

    //printf("%d\n", chessBoard[0][7]); -> debugger


    while(1){
        printf("Command: ");
        lastCharacter = getCommandWord(cmd, MAX_COMMAND_TOKEN_LENGTH);

        if(!strcmp(cmd, "quit")){
            printf("\nExiting Game\n");
            break;
        }
        else if (!strcmp(cmd, "show")){
            if(lastCharacter != '\n'){
                printf("\nERROR\n\n");
            }
            else{
                printf("\n");
                printBoard();
                printf("\n");
            }
        }else if (!strcmp(cmd, "mv")){
            if(lastCharacter == '\n'){
                printf("\nERROR\n\n");
            }
            else{
                handleMove();
            }
        }
        else if (!strcmp(cmd, "cp")){
            if(lastCharacter == '\n'){
                printf("\nERROR\n\n");
            }
            else{
                handleCapture();
            }
        }
        else{
            printf("\nINVALID COMMAND\n");
            while(lastCharacter != '\n')
                lastCharacter = getCommandWord(cmd, MAX_COMMAND_TOKEN_LENGTH);
        }
    }

}
