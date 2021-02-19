#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CELLS_ROW 8
#define MAX_CELLS_COLUMN 8
#define MAX_COMMAND_TOKEN_LENGTH 15
#define OUT_OF_BOUNDS 8

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
        printf("%d    *  ", (OUT_OF_BOUNDS - x));
        for(int y = 0; y < MAX_CELLS_ROW ; y++){
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
    char token[MAX_COMMAND_TOKEN_LENGTH], inputx;
    int column = 0, row = 0;

    if(getCommandWord(token, MAX_CELLS_COLUMN) != '\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n');
        return;
    }else{

       inputx = token[0];
       row = token[1] - '0';

       switch(inputx){
           case 'a':
                column = 0;
                break;
            case 'b':
                column = 1;
                break;
            case 'c' :
                column = 2;
                break;
            case 'd' :
                column = 3;
                break;
            case 'e' :
                column = 4;
                break;
            case 'f' :
                column = 5;
                break;
            case 'g' :
                column = 6;
                break;
            case 'h' :
                column = 7;
                break;
            default:
                column = OUT_OF_BOUNDS;
                break;
       }

       int cell;
       //int *p;

       //p = &cell;

       if(column != OUT_OF_BOUNDS){
            cell = chessBoard[OUT_OF_BOUNDS - row][column];
       }
       else{
           printf("\nINVALID INPUT\n\n");
           return;
       }

       switch(abs(cell)){
           //debugger printouts -> will be replaced with calling move function depending on piece
            case 1 :
                if((cell * -1) > 0){
                    printf("\nTHIS IS A BLACK PAWN\n");
                    //call to move pawn
                }
                else if((cell * -1) < 0){
                    printf("\nTHIS IS A WHITE PAWN\n");
                    //call to move pawn
                }
                break;
            case 4 :
                if((cell * -1) > 0){
                    printf("\nTHIS IS A BLACK ROOK\n");
                    //call to move rook
                }
                else if((cell * -1) < 0){
                    printf("\nTHIS IS A WHITE ROOK\n");
                    //call to move rook
                }
                break;
            case 2 :
                if((cell * -1) > 0){
                    printf("\nTHIS IS A BLACK KINGHT\n");
                    //call to move knight
                }
                else if((cell * -1) < 0){
                    printf("\nTHIS IS A WHITE KNIGHT\n");
                    //call to move knight
                }
                break;
            case 3 :
                if((cell * -1) > 0){
                    printf("\nTHIS IS A BLACK BISHOP\n");
                    //call to move bishop
                }
                else if((cell * -1) < 0){
                    printf("\nTHIS IS A WHITE BISHOP\n");
                    //call to move bishop
                }
                break;
            case 5 :
                if((cell * -1) > 0){
                    printf("\nTHIS IS A BLACK QUEEN\n");
                    //call to move queen
                }
                else if((cell * -1) < 0){
                    printf("\nTHIS IS A WHITE QUEEN\n");
                    //call to move queen
                }
                break;
            case 6 :
                if((cell * -1) > 0){
                    printf("\nTHIS IS A BLACK KING\n");
                    //call to move king
                }
                else if((cell * -1) < 0){
                    printf("\nTHIS IS A WHITE KING\n");
                    //call to move king
                }
                break;
            default :
                printf("\nCELL IS EMPTY\n\n");
                break;
       }

            //debugger printouts!!!!
            printf("Cell : %d\n", cell);
            printf("column : %d\n", column + 1);
            printf("row : %d\n\n", row);
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
    printf("mv <AB> <ab>");    printf("\t\tMoves AB to position ab\n");
    printf("cp <AB> <ab>");    printf("\t\tAB captures ab\n");
    printf("show"); printf("\t\t\tPrints out board\n");
    printf("quit"); printf("\t\t\tQuits the game\n\n");

    //printf("%d\n", chessBoard[0][7]); // debugger
    //printf("%d\n", chessBoard[7][5]); //debugger = 3

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
