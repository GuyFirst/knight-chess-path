#pragma once
#include "allInclude.h"

// CONSTANTS //
#define ROWS 5
#define COLS 5
#define OPTIONAL_KNIGHT_MOVES 8

// CHESS DEF //
typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;

//---------- CHESS POSITION LIST------------//
typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;

//------------ FUNC DECLARATIONS ------------//
void      	processMoves(chessPos knightPos, chessPos** knightMovesArr, int* curr, int* phSize); //checks if the pos is valid and insert it to arr
chessPos* 	arrForKnightPos(chessPos knightPos, int* logSize); //builds an array of next possible knight positions for curr chessPos 
chessPosArray***validKnightMoves(); //the main func the creates and returns the chessboard arrayfrom Q1
bool 		isValidMove(chessPos optionalKnightPos); //checks if the knight can move to the suggested spot
void 		createATable(chessPosList lst, int board[COLS][ROWS]); //creates a table for the given lst
void 		printTable(chessPosList lst); //prints the table
chessPos* 	chessPosToBoardPos(chessPos Pos); //converts the chess positionto a position in the board
void 		checkAllocation(void* ptr); //checks allocation for dynamic array
void 		displayBoard(chessPosCell* curr);//removes duplicates in list
void 		display(chessPosList* lst); //displaying a chess board from Q2
bool 		isEmptyChessList(chessPosList lst);//check if the list is empty
void 		freeArrForKnightPos(chessPos* knightMovesArr); //freeing arr for knight positions
void 		freeValidKnightMoves(chessPosArray*** validMoves); //freeing the whole chess board of kninght positions


