#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

int pawnMoves(int row1, int column1, int row2, int column2){
    int rank;
    int file;

    rank = row2 - row1;
    file = column2 - column1;

    int frontCellWhite = chessBoard[OUT_OF_BOUNDS - (row1 + 1)][column1];
    int frontCellBlack = chessBoard[OUT_OF_BOUNDS - (row1 - 1)][column1];

    int destinationCell = chessBoard[OUT_OF_BOUNDS - row2][column2];

    if((currentTurn == 0) && (destinationCell == 0) && (frontCellWhite == 0)){
        if((row1 == 2) && (file == 0)){
           if((rank <= 2) && (rank > 0)){
               return 1;
           }else{
               printf("INVALID MOVE!\n");
               return 0;
           }
        }
        else if((rank == 1) && (file == 0)){
            return 1;
        }
        else{
            printf("INVALID MOVE!\n");
            return 0;
        }
    }
    else if((currentTurn == 1) && (destinationCell == 0) &&(frontCellBlack == 0)){
        if((row1 == 7) && (destinationCell == 0)){
            if((rank >= -2) && (file == 0)){
                return 1;
            }else{
                printf("INVALID MOVE!\n");
                return 0;
            }
        }
        else if((rank == -1) && (file == 0)){
            return 1;
        }
        else{
            printf("INVALID MOVE!\n");
            return 0;
        }
    }
    else if((currentTurn == 0) && (destinationCell != 0)){
        if((rank == 1) && ((file == 1) || (file == -1))){
            return 1;
        }
        else{
            printf("INVALID MOVE!\n");
            return 0;
        }
    }
    else if((currentTurn == 1) && (destinationCell != 0)){
        if((rank == -1) && ((file == 1) || (file == -1))){
            return 1;
        }
        else{
            printf("INVALID MOVE!\n");
            return 0;
        }
    }
    else{
        printf("INVALID MOVE!\n");
        return 0;
    }

    return 0;

}

int kingMoves(int row1, int column1, int row2, int column2){
    int rank;
    int file;

    rank = row2 - row1;
    file = column2 - column1;

    if(((file == 0) || (file == 1) || (file == -1)) && ((rank == 1) || (rank == -1))){
        return 1;
    }
    else if( ((rank == 0) || (rank == 1) || (rank == -1)) && ( (file == 1) || (file == -1) ) ){
        return 1;
    }
    else{
        printf("INVALID MOVE!\n\n");
        return 0;
    }
    return 0;

}

int knightMoves(int row1, int column1, int row2, int column2){

    int rank;
    int file;

    rank = row1 - row2;
    file = column1 - column2;

    if((rank != 0) && (file != 0)){

        if(file == 2 || file == -2){
            if (rank == 1 || rank == -1){
                return 1;
            }
            else{
                printf("INVALID MOVE\n");
                return 0;
            }
        }
        else if(file == 1 || file == -1){
            if (rank == 2 || rank == -2){
                return 1;
            }
            else{
                printf("INVALID MOVE\n");
                return 0;
            }

        }
        else{
            printf("INVALID MOVE\n");
            return 0;
        }

    }
    else{
        printf("INVALID MOVE!\n");
        return 0;
    }
    return 0;
}

#endif // PIECES_H_INCLUDED
