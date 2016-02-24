/* Practice C code */
/* attempt to write chess*/

// import libraries
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// set up a structure to represent a space on the board
typedef struct Space {
	int color; // 0 = empty, 1 = White, -1 = Black
	int aNum; // the numlocation of the space on the board
	int aLett; // the letterlocation of the space on the board
	char *piece; // the name of the pice on that square
	char *name; // string version of address
} Space;

// function that tells if there are any pieces between start and given
bool noneBetween(Space s, Space g, Space *board[8][8]) {
	while (s.aLett != g.aLett && s.aNum != g.aNum) {
		if (s.aLett != g.aLett) {
			s.aLett += (g.aLett - s.aLett) > 0 ? 1 : -1;
		}
		if (s.aNum != g.aNum) {
			s.aNum += (g.aNum - s.aNum) > 0 ? 1 : -1;
		}
		if (board[s.aNum][s.aLett]->color != 0) {
			return false;
		}
	}
	return true;
}

// returns true if piece on given space can move to given space
bool moveOkay(Space start, Space given, Space *board[8][8]) {
	switch(start.piece[0]) {

	// if the piece is a pawn...
	case 'p' /* pawn */ :  
		// if move is 1 forward:
		if ((given.aLett == start.aLett) && // given and start are in the same column
			(given.aNum == start.aNum + start.color) && // Space of given is above if white, below if black
			(given.color != start.color)) { // given is not the same color as start
			return true;
		}
		// if move is to take enemy pawn:
		else if (((given.aLett == start.aLett - 1) || // given is 1 left of start
			(given.aLett == start.aLett + 1)) && // given is 1 right of start
			(given.aNum == start.aNum + start.color) && // row of given is above if white, below if black 
			(given.color == start.color * -1)) { // given is opposite color as start
			return true;
		}
		break;

	// if the piece is a knight...
	case 'k' /* knight */ :	
		// if move is up or down 2 and 1 to side:
		if (((given.aLett == start.aLett + 2) || // given is 2 above start
			(given.aLett == start.aLett - 2)) && // given is 2 below start 
			((given.aNum == start.aNum - 1) || // given is 1 left of start
			(given.aNum == start.aNum + 1)) && // given is 1 right of start
			(given.color != start.color) ) { // given is not the same color as start
			return true;
		}
		// if move is up or down 1 and 2 to side:
		else if (((given.aLett == start.aLett + 1) || // given is 1 above start
			(given.aLett == start.aLett - 1)) && // given is 1 below start
			((given.aNum == start.aNum - 2) || // given is 2 left of start
			(given.aNum == start.aNum + 2)) && // given is 2 right of start
			(given.color != start.color) ) { // given is not the same color as start
			return true;
		}
		break;

	// if the piece is a rook...
	case 'r' /* rook */ :
		// if the move is within the row or column:
		if (((start.aLett == given.aLett) || // given is same row as start
			(start.aNum == given.aNum)) &&  // given is same column as start
			(noneBetween(start, given, board)) && // there are no occ spaces between
			(given.color != start.color)) { // given is not the same color as start 
			return true;
		}
		break;

	// if the piece is a bishop...
	case 'b' /* bishop */ :
		// if the move is left or right diagonal:
		if ((((given.aNum - start.aNum) / // rise
			(given.aLett - start.aLett)) // run
			== (1 || -1)) && // has a slope of 1
			(noneBetween(start, given, board)) && // there are no occ spaces between
			(given.color != start.color)) { // given is not the same color as start 
			return true;
		}
		break;

	// if the piece is a queen...
	case 'q' /* queen */ :
		// if the move is within the row or column:
		if (((start.aLett == given.aLett) || // given is same row as start
			(start.aNum == given.aNum)) &&  // given is same column as start
			(noneBetween(start, given, board))) { // there are no occ spaces between
			return true;
		}
		// if the move is left or right diagonal:
		else if ((((given.aNum - start.aNum) / // rise
			(given.aLett - start.aLett)) // run
			== (1 || -1)) && // has a slope of 1
			(noneBetween(start, given, board)) && // there are no occ spaces between
			(given.color != start.color)) { // given is not the same color as start 
			return true;
		}
		break;

	// if the piece is a king...
	case 'K' /* king */ :
		//TODO add in if king is in check
		if (// if move is left or right 1:
			(((start.aNum == given.aNum) && // given is in same column as start
			((start.aLett == given.aLett - 1) || // given is left of start
			(start.aLett == given.aLett + 1)))  // given is right of start    
			// if move is above or below 1:
			|| ((start.aLett == given.aLett) && // given is same row as start
			((start.aNum == given.aNum - 1) || // given is below start
			(start.aNum == given.aNum + 1)))  // given is above start         
			// if move is diagonal by 1:
			|| (((start.aLett == given.aLett - 1) || // given is left of start
			(start.aLett == given.aLett + 1)) &&  // given is right of start
			((start.aNum == given.aNum + 1) ||   // given is above start
			(start.aNum == given.aNum - 1)))) && // given is below start
			(given.color != start.color)) { // given is not the same color as start  
			return true;
		}
		break;

	default :
		return false;
	}
}

// takes string and returns Space with matching name	
Space findName(char* s, Space *board[8][8]) {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (strcmp(board[x][y]->name, s) == 0) {
				return *board[x][y];
			}
		}
	}
}

// the main function
int main(int argc, char const *argv[])
{
	// declare variables:
	bool quit = false;
	Space *board[8][8]; // should be  Space ***board;  ?

	// memory allocation:
	/*size_t spaceSize = 8;//sizeof(Space*);	
	board = malloc(sizeof(board) * spaceSize); 
	for (int i = 0; i < 8; ++i)	{
		board[i] = (Space*) malloc(sizeof *board[i] * 8);
		for (int x = 0; x < 8; x++) {
			board[i][x] = malloc(sizeof(Space));
		}
	}*/

	// initilize the board at start time
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			board[x][y]->aNum = x;  // initialize aNum 
			board[x][y]->aLett = y; // initialize aLett
			if (x < 2) {
				board[x][y]->color = 1; // set white 
			}
			else if (x < 6) {
				board[x][y]->color = 0; // set neutral
			}
			else {
				board[x][y]->color = -1; // set black
			}
		}
	}

	// initialize pieces  TODO improve the shit out of this
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if ((x > 1) && (x < 6)) {
				board[x][y]->piece = "";
			}
			else if ((x == 1) || (x == 6)) {
				board[x][y]->piece = "pawn";
			}
			else if ((y == 0) || (y == 7)){
				board[x][y]->piece = "rook";
			}
			else if ((y == 1) || (y == 6)){
				board[x][y]->piece = "knight";
			}
			else if ((y == 2) || (y == 5)){
				board[x][y]->piece = "bishop";
			}
		}
	}

	// initialize the unique pieces
	board[0][3]->piece = "King";
	board[7][3]->piece = "King";
	board[0][4]->piece = "queen";
	board[7][4]->piece = "queen";
	
	// initialize names
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			char* n;
			board[x][y]->name = sprintf(n, "%c%d", (41 + x), y);
		}
	}

	// while loop to run the game
	while (quit == false) {

		// print the board
		for (int x = 0; x < 8; x++) {
			int i = 7;
			printf("---------------------------------------------\n");
			printf("%s | %s | %s | %s | %s | %s | %s | %s \n",
				board[x][i]->name, board[x][i-1]->name, board[x][i-2]->name, board[x][i-3]->name, 
				board[x][i-4]->name, board[x][i-5]->name, board[x][i-6]->name, board[x][i-7]->name);
		}
		printf("---------------------------------------------\n");
		fflush(stdout);

		// print prompt
		printf("Please enter your move in the following format:\n"
 		   "<piece name> <destination>\n\n");
	
		// scan for input
		char* s1; char* s2;
		scanf(">> %s %s", s1, s2);
	
		// translate into move
		Space start = findName(s1, board);
		Space given = findName(s2, board);

		// check if move is okay with "moveOkay"
		if (moveOkay(start, given, board)) {
			given.color == start.color;
			given.piece == start.piece;
			start.color == 0;
			start.piece == "none";
		}
		else {
			printf("You can't do that\n");
		}
	}
	return 0;
}
