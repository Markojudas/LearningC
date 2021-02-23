#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CELLS 8
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

static int currentTurn = 0;

void printBoard(){
    char *header = "  a |  b |  c |  d |  e |  f |  g |  h |\n";

    //starting to print the board
    printf("BOARD* ");

    printf("%s", header);
    printf("\t****************************************\n");

    for(int x = 0; x < MAX_CELLS; x++){
        printf("%d    *  ", (OUT_OF_BOUNDS - x));
        for(int y = 0; y < MAX_CELLS; y++){
            printf("%2d |", chessBoard[x][y]);
            printf(" ");
        }
        printf("\n\n");
    }
}

char getCommandWord(char command[], int maxLength) {
	char lastCharacter;
	int i;

    for(i = 0; (lastCharacter = getchar()) == ' '; i++); //skip leading white space

    if(lastCharacter == '\n'){
        command[0] = '\0';
        return lastCharacter;
    }

    command[0] = lastCharacter;
	for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
	lastCharacter = command[i];
	command[i] = '\0';
	return lastCharacter;
}

void getCell(char token[], int *cellContent, int *row, int *column){

     char inputx;

     inputx = token[0];
     *row = token[1] - '0';

    switch(inputx){
           case 'a':
                *column = 0;
                break;
            case 'b':
                *column = 1;
                break;
            case 'c' :
                *column = 2;
                break;
            case 'd' :
                *column = 3;
                break;
            case 'e' :
                *column = 4;
                break;
            case 'f' :
                *column = 5;
                break;
            case 'g' :
                *column = 6;
                break;
            case 'h' :
                *column = 7;
                break;
            default:
                *column = OUT_OF_BOUNDS;
                break;
       }
       if((*column < OUT_OF_BOUNDS && *column >= 0) && (*row <= OUT_OF_BOUNDS && *row > 0)){
            *cellContent = chessBoard[OUT_OF_BOUNDS - *row][*column];
       }
       else{
           printf("\nINVALID INPUT: ");
           return;
       }
}

int pawnMoves(int row1, int column1, int row2, int column2){
    int rank, file, frontCellWhite, frontCellBlack, destinationCell;

    rank = row2 - row1;
    file = column2 - column1;

    frontCellWhite = chessBoard[OUT_OF_BOUNDS - (row1 + 1)][column1];
    frontCellBlack = chessBoard[OUT_OF_BOUNDS - (row1 - 1)][column1];
    destinationCell = chessBoard[OUT_OF_BOUNDS - row2][column2];

    if((currentTurn == 0) && (destinationCell == 0) && (frontCellWhite == 0)){
        if((row1 == 2) && (file == 0)){
           if((rank <= 2) && (rank > 0)){
               return 1;
           }else{
               printf("\nINVALID MOVE!\n");
               return 0;
           }
        }
        else if((rank == 1) && (file == 0)){
            return 1;
        }
        else{
            printf("\nINVALID MOVE!\n");
            return 0;
        }
    }
    else if((currentTurn == 1) && (destinationCell == 0) &&(frontCellBlack == 0)){
        if((row1 == 7) && (destinationCell == 0)){
            if((rank >= -2) && (file == 0)){
                return 1;
            }else{
                printf("\nINVALID MOVE!\n");
                return 0;
            }
        }
        else if((rank == -1) && (file == 0)){
            return 1;
        }
        else{
            printf("\nINVALID MOVE!\n");
            return 0;
        }
    }
    else if((currentTurn == 0) && (destinationCell != 0)){
        if((rank == 1) && ((file == 1) || (file == -1))){
            return 1;
        }
        else{
            printf("\nINVALID MOVE!\n");
            return 0;
        }
    }
    else if((currentTurn == 1) && (destinationCell != 0)){
        if((rank == -1) && ((file == 1) || (file == -1))){
            return 1;
        }
        else{
            printf("\nINVALID MOVE!\n");
            return 0;
        }
    }
    else{
        printf("\nINVALID MOVE!\n");
        return 0;
    }
    return 0;
}

int rookMoves(int row1, int column1, int row2, int column2){
    int rank, file;

    rank = row2 - row1;
    file = column2 - column1;

    if ((file != 0) && (rank == 0)){
        if(file * -1 < 0){
            for(int i = column1 + 1; i < column2; i++){
                if(chessBoard[OUT_OF_BOUNDS - row1][i] != 0){
                    printf("\nTHERE IS A PIECE IN BETWEEN. CANNOT MOVE\n\n");
                    return 0;
                    break;
                }
            }
        }
        if (file * -1 > 0){
            for(int i = column1 - 1; i > column2; i--){
                if(chessBoard[OUT_OF_BOUNDS - row1][i] != 0){
                    printf("\nTHERE IS A PIECE IN BETWEEN. CANNOT MOVE\n\n");
                    return 0;
                    break;
                }
            }
        }
        if(((file < OUT_OF_BOUNDS) || (file > -(OUT_OF_BOUNDS))) && (rank == 0)){
            return 1;

        }
        else{
            printf("\nINVALID MOVE\n\n");
            return 0;
        }
    }
    else if((rank != 0) && (file == 0)){
        if(rank * -1 < 0){
            for(int i = row1 + 1; i < row2; i++){
                if(chessBoard[OUT_OF_BOUNDS - i][column1] != 0){
                    printf("\nTHERE IS A PIECE IN BETWEEN. CANNOT MOVE\n\n");
                    return 0;
                    break;
                }

            }
        }
        if(rank * -1 > 0){
            for(int i = row1 - 1; i > row2; i--){
                if(chessBoard[OUT_OF_BOUNDS - i][column1] != 0){
                    printf("\nTHERE IS A PIECE IN BETWEEN. CANNOT MOVE\n\n");
                    return 0;
                    break;
                }

            }
        }
        if((file == 0) && ((rank < OUT_OF_BOUNDS) || (rank > -(OUT_OF_BOUNDS)))){
            return 1;
        }
    }
    else{
        printf("\nINVALID MOVE\n\n");
        return 0;
    }
    return 0;
}

int bishopMoves(int row1, int column1, int row2, int column2){
    int rank, file, absoluteRank, absoluteFile, i;

    rank = row2 - row1;
    file = column2 - column1;

    absoluteRank = abs(rank);
    absoluteFile = abs(file);

    if((rank != 0) && (file != 0)){
        if(rank * -1 < 0){
            i = row1 + 1;
            if(file * -1 > 0){
                for(int j = column1-1; j > column2; j--, i++){
                    if(chessBoard[OUT_OF_BOUNDS - i][j] != 0){
                        printf("\nTHERE IS A PIECE IN BETWEEN. CANNOT MOVE\n\n");
                        return 0;
                        break;
                    }
                }
            }
            if(file * - 1 < 0){
                for(int j = column1+1; j < column2; j++, i++){
                    if(chessBoard[OUT_OF_BOUNDS - i][j] != 0){
                        printf("\nTHERE IS A PIECE IN BETWEEN. CANNOT MOVE\n\n");
                        return 0;
                        break;
                    }
                }
            }
        }
        if(rank * -1 > 0){
            i = row1 - 1;
            if(file * -1 < 0){
                for(int j = column1+1; j < column2; j++, i--){
                    if(chessBoard[OUT_OF_BOUNDS - i][j] != 0){
                        printf("\nTHERE IS A PIECE IN BETWEEN. CANNOT MOVE\n\n");
                        return 0;
                        break;
                    }
                }
            }
            if(file * -1 > 0){
                for(int j = column1-1; j > column2; j--, i--){
                    if(chessBoard[OUT_OF_BOUNDS - i][j] != 0){
                        printf("\nTHERE IS A PIECE IN BETWEEN. CANNOT MOVE\n\n");
                        return 0;
                        break;
                    }
                }
            }
        }
        if(absoluteRank == absoluteFile){
            return 1;
        }
        else{
            printf("\nINVALID MOVE\n\n");
            return 0;
        }
    }
    else{
        printf("\nINVALID MOVE\n\n");
        return 0;
    }
    return 0;
}

int queenMoves(int row1, int column1, int row2, int column2){

    int rank, file, absoluteRank, absoluteFile;

    rank = row2 - row1;
    file = column2 - column1;
    absoluteRank = abs(rank);
    absoluteFile = abs(file);

    if(absoluteFile == absoluteRank){
        //moves as a bishop
        int queenBishopMove = bishopMoves(row1, column1, row2, column2);
        if(queenBishopMove == 1){
            return 1;
        }
    }
    else if((file == 0 && rank !=0) || (rank == 0 && file != 0)){
        //moves as rook
        int queenRookMove = rookMoves(row1, column1, row2, column2);
        if(queenRookMove == 1){
            return 1;
        }
    }
    else{
        //illegal move
        printf("\nINVALID MOVE!\n\n");
    }
    return 0;
}

int kingMoves(int row1, int column1, int row2, int column2){
    int rank, file;

    rank = row2 - row1;
    file = column2 - column1;

    if(((file == 0) || (file == 1) || (file == -1)) && ((rank == 1) || (rank == -1))){
        return 1;
    }
    else if( ((rank == 0) || (rank == 1) || (rank == -1)) && ( (file == 1) || (file == -1) ) ){
        return 1;
    }
    else{
        printf("\nINVALID MOVE!\n\n");
        return 0;
    }
    return 0;

}

int knightMoves(int row1, int column1, int row2, int column2){

    int rank, file;

    rank = row1 - row2;
    file = column1 - column2;

    if((rank != 0) && (file != 0)){

        if(file == 2 || file == -2){
            if (rank == 1 || rank == -1){
                return 1;
            }
            else{
                printf("\nINVALID MOVE\n");
                return 0;
            }
        }
        else if(file == 1 || file == -1){
            if (rank == 2 || rank == -2){
                return 1;
            }
            else{
                printf("\nINVALID MOVE\n");
                return 0;
            }

        }
        else{
            printf("\nINVALID MOVE\n");
            return 0;
        }

    }
    else{
        printf("\nINVALID MOVE!\n");
        return 0;
    }
    return 0;
}

char getFileName(int file){

    char fileName;

    switch(file){
        case 0 :
            return fileName = 'a';
            break;
        case 1 :
            return fileName = 'b';
            break;
        case 2 :
            return fileName = 'c';
            break;
        case 3 :
            return fileName = 'd';
            break;
        case 4 :
            return fileName = 'e';
            break;
        case 5 :
            return fileName = 'f';
            break;
        case 6 :
            return fileName = 'g';
            break;

        case 7 :
            return fileName = 'h';
            break;

        default :
            return fileName = '0';
            break;
    }
    return '0';
}

void replaceCell(int row1, int column1, int row2, int column2){

    int tempCell = chessBoard[OUT_OF_BOUNDS - row1][column1];

    chessBoard[OUT_OF_BOUNDS - row1][column1] = 0;
    chessBoard[OUT_OF_BOUNDS - row2][column2] = tempCell;

    printBoard();
    printf("\n");

    if(currentTurn == 0){
        currentTurn = 1;
    }else{
        currentTurn = 0;
    }
}

void movePiece(int cell1, int row1, int column1, int cell2, int row2, int column2){

    char fileName2 = getFileName(column2);

    switch(abs(cell1)){
        case 1 :
            if((cell1 * -1) > 0){
                if(pawnMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING BLACK PAWN TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            else if((cell1 * -1) < 0){
                if(pawnMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING WHITE PAWN TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            break;
        case 4 :
            if((cell1 * -1) > 0){
                if(rookMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING BLACK ROOK TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            else if((cell1 * -1) < 0){
                if(rookMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING WHITE ROOK TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            break;
        case 2 :
            if((cell1 * -1) > 0){
                if(knightMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING BLACK KNIGHT TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            else if((cell1 * -1) < 0){
                if(knightMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING WHITE KNIGHT TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            break;
        case 3 :
            if((cell1 * -1) > 0){
                if(bishopMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING BLACK BISHOP TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            else if((cell1 * -1) < 0){
                if(bishopMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING WHITE BISHOP TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            break;
        case 5 :
            if((cell1 * -1) > 0){
                if(queenMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING BLACK QUEEN TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            else if((cell1 * -1) < 0){
                if(queenMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING WHITE QUEEN TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            break;
        case 6 :
            if((cell1 * -1) > 0){
                if(kingMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING BLACK KING TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            else if((cell1 * -1) < 0){
                if(kingMoves(row1, column1, row2, column2) == 1){
                    printf("\nMOVING WHITE KING TO %c%d!\n\n", fileName2, row2);
                    replaceCell(row1, column1, row2, column2);
                }
            }
            break;
        default :
            printf("\nCELL IS EMPTY\n\n");
            break;
       }
}

void handleMove(){
    char token1[MAX_COMMAND_TOKEN_LENGTH];
    char token2[MAX_COMMAND_TOKEN_LENGTH];
    int firstCell, secondCell, cellContent, row1, row2, column1, column2;
    int *x; int *row1Pointer; int *row2Pointer; int *column1Pointer; int *column2Pointer;

    x = &cellContent;
    row1Pointer = &row1;
    row2Pointer = &row2;
    column1Pointer = &column1;
    column2Pointer = &column2;

    if(getCommandWord(token1, MAX_COMMAND_TOKEN_LENGTH) == '\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token1, MAX_COMMAND_TOKEN_LENGTH) == '\n');
        return;
    }

    if(getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) !='\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) != '\n');
        return;
    }

       getCell(token1, x, row1Pointer, column1Pointer);
       firstCell = *x;
       getCell(token2, x, row2Pointer, column2Pointer);
       secondCell = *x;

    if(row1 > OUT_OF_BOUNDS || row2 > OUT_OF_BOUNDS || column1 >= OUT_OF_BOUNDS || column2 >= OUT_OF_BOUNDS ||
        row1 <= 0 || row2 <= 0 || column1 < 0 || column2 < 0){

        printf("OUT OF BOUND INPUT\n\n");
        return;
    }

    if((currentTurn == 0)){

        if(firstCell * -1 > 0){
            printf("\nIT'S NOT YOUR TURN YET\n\n");
            return;
        }

        if(secondCell != 0){
            printf("\nCANNOT MOVE HERE! POSITION IS TAKEN\n\n");
            return;
        }
        if(firstCell != 0){
            movePiece(firstCell, row1, column1, secondCell, row2, column2);
        }else{
            printf("\nNOTHING TO MOVE\n\n");
            return;
        }
    }
    else if((currentTurn == 1)){
        if(firstCell * -1 < 0){
            printf("\nIT'S NOT YOUR TURN YET\n\n");
            return;
        }

        if(secondCell != 0){
            printf("\nCANNOT MOVE HERE! POSITION IS TAKEN\n\n");
            return;
        }

        if(firstCell != 0){
            movePiece(firstCell, row1, column1, secondCell, row2, column2);
        }else{
            printf("\nNOTHING TO MOVE\n\n");
            return;
        }
    }
    else{
        printf("\nILLEGAL MOVE!!\n\n");
        return;
    }
}

void handleCapture(){
    char token1[MAX_COMMAND_TOKEN_LENGTH];
    char token2[MAX_COMMAND_TOKEN_LENGTH];
    int firstCell, secondCell, cellContent, row1, row2, column1, column2;
    int *x; int *row1Pointer; int *row2Pointer; int *column1Pointer; int *column2Pointer;

    x = &cellContent;
    row1Pointer = &row1;
    row2Pointer = &row2;
    column1Pointer = &column1;
    column2Pointer = &column2;

    if(getCommandWord(token1, MAX_COMMAND_TOKEN_LENGTH) == '\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token1, MAX_COMMAND_TOKEN_LENGTH) == '\n');
        return;
    }

    if(getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) !='\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) != '\n');
        return;
    }

       getCell(token1, x, row1Pointer, column1Pointer);
       firstCell = *x;
       getCell(token2, x, row2Pointer, column2Pointer);
       secondCell = *x;

    if(row1 > OUT_OF_BOUNDS || row2 > OUT_OF_BOUNDS || column1 >= OUT_OF_BOUNDS || column2 >= OUT_OF_BOUNDS ){
            printf("OUT OF BOUNDS\n\n");
            return;
    }

    if((secondCell == 0)){
                printf("\nNOTHING TO CAPTURE\n\n");
                return;
    }
    else{
        if((currentTurn == 0) && (firstCell * -1 < 0)){
            if(secondCell * -1 < 0){
                printf("\nTHIS IS A WHITE PIECE!\n\n");
                return;
            }
            if(firstCell != 0){
                movePiece(firstCell, row1, column1, secondCell, row2, column2);
            }else{
                printf("\nNO PIECE TO MOVE!\n\n");
                return;
            }
        }
        else if((currentTurn == 1) && (firstCell * -1 > 0)){
            if(secondCell * -1 > 0){
                printf("\nTHIS IS A BLACK PIECE!\n\n");
            }
            if(firstCell != 0){
                movePiece(firstCell, row1, column1, secondCell, row2, column2);
            }else{
                printf("\nNO PIECE TO MOVE!!\n\n");
                return;
            }
        }
        else{
            printf("\nIT'S NOT YOUR TURN YET!!\n\n");
        }
    }
}

void handleHelp(){
    printf("\n************************************************\n");
    printf("\t\tCHESS GAME : HELP\n");
    printf("************************************************\n");
    printf("\nAa = letter from a-h\nBb = numbers from 1-8\nPositive Numbers = White Pieces\nNegative Numbers = Black Pieces\n");
    printf("\nPIECES:");
    printf("\n1 = Pawn\n2 = Knight\n3 = Bishop\n4 = Rook\n5 = Queen\n6 = King\n");
    printf("\nCommand List:\n");
    printf("mv <AB> <ab>");    printf("\t\tMoves AB to position ab\n");
    printf("cp <AB> <ab>");    printf("\t\tAB captures ab\n");
    printf("show"); printf("\t\t\tPrints out board\n");
    printf("help"); printf("\t\t\tPrints legend & list of commands\n");
    printf("quit"); printf("\t\t\tQuits the game\n\n");

    printBoard();
}

int main()
{
    char cmd[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;

    printf("*********************************************\n");
    printf("\t\tCHESS GAME!!!\n");
    printf("*********************************************\n");
    printf("'help' for legend & list of commands\n\n");

    printBoard();
    printf("\n");

    while(1){

        if(currentTurn == 0){
           printf("WHITE TURN: ");
        }else{
            printf("BLACK TURN: ");
        }

        lastCharacter = getCommandWord(cmd, MAX_COMMAND_TOKEN_LENGTH);

        if(!strcmp(cmd, "quit")){
            printf("\nExiting Game\n");
            break;
        }
        else if (!strcmp(cmd, "help")){
            if(lastCharacter != '\n'){
                printf("\nERROR\n");
            }
            else{
                handleHelp();
            }
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
