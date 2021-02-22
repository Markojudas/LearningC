CHESS GAME!! README FILE:

Programmer: 	Jose R. Hernandez
PantherID:		1398700
Course: 		Systems Programming - COP4338 U01 1211
Instructor:		Kianoosh G. Boroojeni, Ph.D.
Semester:		Spring 2021


This is a simple game of chess. I admit the code could be a bit cleaner but this is the best I was able to do to handle some situations as I was writing the code.

	Implemented Functions:
 
 1) The program starts by initializing a table simmulating a chess board
 
 2) The program displays the list of commands and prints the chess board. 
 
 2)	The program asks to first move a white piece. After move (mv) or capture (cp) functions are called it then asks for the black piece to move - oscilating until the end of the program.
	I have initialized a variable to keep track (currentTurn). if currentTurn = 0 then it is the WHITE TURN, else if it's 1 then it is the BLACK TURN.
 
 3)	The program gives the object to quit the game.
 
 4) I am using the "lastCharacter" approach to get the command word & tokenize the string

	Main Functions:
	1) Show
		Using a nested for loop I am displaying the multi-d array (chess table). Array[0][0] is printed out as rank 8 while Array[7][0] is printed as rank 1.
	
	2) mv <AB> <ab>
		*I used this command as the building block of my program*
		This command calls the handleMove() function.
		It first tokenizes the string & delcares variables and corresponding pointers for these variables
		
		The handleMove() function then calls the getCell() function for the source location (firstCell) and the destination (secondCell). This is used to identify the piece and whether it is a white or black piece.
		This is also used to determine the correct piece is chosen depending of the turn. Then it calls the movePiece() function.
		
		Please note that the getCell() function breaks down the input and locates said input in the array. Whereas 'a1' corresponds to array[7][0] and h8 corresponds to aray[0][7]
		
		The movePiece() function works for either turn and calls for the function for the corresponding chess piece. Then it calls swap or replaceCell() function. This works for the 'mv' and 'cp' commands.
		
		Lastly, if the destination cell is empty of (0), then it swaps. If the destination cell is NOT empty an error will be displayed.
		
	3) cp <AB> <ab>
		This command calls the handleCapture() function.
		
		*this command is very similar to the move command. The only difference is that it checks whether the destination cell is occupied with the oposite color piece.
		If so, then the movePiece() function is called and the same steps are performed.
		
	4) quit
		This terminates the program
		

	Piece Movements:
	1) 1/-1 : Pawn
		It first checks if there is a piece in between the source cell and destination cell.
		If there isn't a piece in between, then it checks if the original row/rank is 2(white) or 7(black). If so, the pawn moves 2 places up (white) or 2 places down (black). Otherwise it just moves one place up/down depending of color.
		
	
	2) 2/-2 : Knight
		
		
