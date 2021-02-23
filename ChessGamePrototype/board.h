#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int currentTurn = 0;

stastic int chessBoard[8][8] = {
    {-4, -2, -3, -5, -6, -3, -2, -4}, //chessBoard[0][0-7]
    {-1, -1, -1, 1, -1, -1, -1, -1}, //chessBoard[1][0-7]
    {0, 0, 0, 0, 0, 0, 0, 0},         //chessBoard[2][0-7]
    {0, 1, 0, 0, 5, 0, 1, 0},         //chessBoard[3][0-7]
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
        printf("\n\n");
    }
}


#endif // BOARD_H_INCLUDED
