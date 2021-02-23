#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

int currentTurn;
static int chessBoard[8][8];
void printBoard();
char getCommandWord(char command[], int maxLength);
void getCell(char token[], int *cellContent, int *row, int *column);
char getFileName(int file);
int pawnMoves(int row1, int column1, int row2, int column2);
int rookMoves(int row1, int column1, int row2, int column2);
int bishopMoves(int row1, int column1, int row2, int column2);
int queenMoves(int row1, int column1, int row2, int column2);
int kingMoves(int row1, int column1, int row2, int column2);
int knightMoves(int row1, int column1, int row2, int column2);
void replaceCell(int row1, int column1, int row2, int column2);
void movePiece(int cell1, int row1, int column1, int cell2, int row2, int column2);
void handleMove();
void handleCapture();



#endif // FUNCTIONS_H_INCLUDED
