CHESS GAME!! README FILE:

Programmer: 		Jose R. Hernandez
PantherID:		1398700
Course: 		Systems Programming - COP4338 U01 1211
Instructor:		Kianoosh G. Boroojeni, Ph.D.
Semester:		Spring 2021


IMPLEMENTED:
1) Initialized the 2d array called chessBoard
2) Implemented a printBoard() function to print out the chessBoard.
3) Implemented a getCommandWord() function to tokenize the command word and user input.
4) Implemented the two main functionalities of the program: mv - Move and cp - Capture (handleMove() and hanldeCapture())
	The move and capture functions are quite similar. The move function checks if the target cell (or destination cell) is empty to be able to even make the move.
	If the destination cell is empty it will determine whether it is the right turn (white-0 or black-1). It also determines if the input are not "out of bounds"
	The Capture function does the same thing but it checks if there is a piece occupying the destination/target cell, if there is it checks if that piece of of the opposite color - white captures black and vice versa
5) Implemented a getCell() function that helps with the above - it returns the content of a given cell
6) Implemented a movePiece() function - this function identifies what kind of piece is making the move (either mere move or capture) and calls the function accordingly. 
	The function calls getFileName() function for aesthetics purposes. if the FILE is 0 through 7 then it returns a letter a-h respectively.
7) The movePiece() function, after the program returns 1 from the given piece function, it then calls the replaceCell() function - which is basically a swap function. The turn is switched from 0 to 1 and vice versa.
8) Implemented the legal moves for all 6 pieces (pawn, rook, knight, bishop, queen and king).
9) Implemented a "Help" function that prints out a legend and the list of commands. 
10) Implement a "quit" command that just terminates the program.

BONUS IMPLEMENTED:
1) Pawn Promotion -> programmed the pawn promotion within the pawnMoves() function. If the white pawn reaches rank 8 (array[0][0-> 7]) the program asks the user whether or not they want to promote the pawn.
	if yes, the program asks to choose between {queen, bishop, rook, knight}. Depending which the choose it replaces the contents of moving cell from 1 to {|6|, |3|, |2|, |4|} representing the chosen piece
	then the function returns 1 to the movePiece() function and to the replaceCell(). This works just the same for the capture function. 

NOT IMPLEMENTED:
1) The program does NOT check whether or not the king is in "check" or even "checkmate"(bonus)
2) DID NOT implement castling or en passant moves (Bonus)

 