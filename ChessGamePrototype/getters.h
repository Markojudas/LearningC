#ifndef GETTERS_H_INCLUDED
#define GETTERS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

char getCommandWord(char command[], int maxLength) {
	char lastCharacter;
	int i;

	for (i = 0; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
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


#endif // GETTERS_H_INCLUDED
