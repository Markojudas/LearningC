#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

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
    int firstCell, cellContent, row1, row2, column1, column2;
    int secondCell;
    int *x;
    x = &cellContent;
    int *row1Pointer; int *row2Pointer; int *column1Pointer; int *column2Pointer;

    row1Pointer = &row1;
    row2Pointer = &row2;
    column1Pointer = &column1;
    column2Pointer = &column2;


    if(getCommandWord(token1, MAX_CELLS_COLUMN) == '\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token1, MAX_COMMAND_TOKEN_LENGTH) == '\n');
        return;
    }

    if(getCommandWord(token2, MAX_CELLS_COLUMN) !='\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token2, MAX_CELLS_COLUMN) != '\n');
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
       }
}

void handleCapture(){
    char token1[MAX_COMMAND_TOKEN_LENGTH];
    char token2[MAX_COMMAND_TOKEN_LENGTH];
    int firstCell, cellContent, row1, row2, column1, column2;
    int secondCell;
    int *x;
    x = &cellContent;
    int *row1Pointer; int *row2Pointer; int *column1Pointer; int *column2Pointer;

    row1Pointer = &row1;
    row2Pointer = &row2;
    column1Pointer = &column1;
    column2Pointer = &column2;

    if(getCommandWord(token1, MAX_CELLS_COLUMN) == '\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token1, MAX_COMMAND_TOKEN_LENGTH) == '\n');
        return;
    }

    if(getCommandWord(token2, MAX_CELLS_COLUMN) !='\n'){
        printf("\nERROR IN INPUT!\n\n");
        while(getCommandWord(token2, MAX_CELLS_COLUMN) != '\n');
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


#endif // MOVES_H_INCLUDED
