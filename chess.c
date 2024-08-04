#include "allInclude.h"


void processMoves(chessPos knightPos, chessPos** knightMovesArr, int* curr, int* phSize)   //this func gets a chessPos, a pointer to an array of chessPos, a pointer to curr, and a pointer to size
{                                                                                          //then it checks if the pos is valid and insert it to arr
    chessPos optionalMove = { knightPos[0], knightPos[1] };

    // Arrays to identify where the next optional knight move is
    int charArr[8] = { -2,-1, 1, 2, 2, 1, -1, -2 };
    int numberArr[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for (int i = 0; i < OPTIONAL_KNIGHT_MOVES; i++)
    {
        optionalMove[0] += charArr[i];
        optionalMove[1] += numberArr[i];

        if (isValidMove(optionalMove))
        {
            (*knightMovesArr)[*curr][0] = optionalMove[0];
            (*knightMovesArr)[*curr][1] = optionalMove[1];
            (*curr)++;

            if (*curr >= *phSize) // If current size exceeds or equals the allocated size, reallocate
            {
                *phSize += 8; // Allocate memory for 8 more moves
                *knightMovesArr = (chessPos*)realloc(*knightMovesArr, (*phSize) * sizeof(chessPos));
                if (!(*knightMovesArr))
                {
                    printf("Memory reallocation failed.\n");
                    exit(-1);
                }
            }
        }
        optionalMove[0] = knightPos[0];
        optionalMove[1] = knightPos[1];
    }
}

chessPos* arrForKnightPos(chessPos knightPos, int* logSize)    //this func recieves a chessPos and a pointer to size,
{                                                              //then it builds an array of next possible positions for curr chessPos
    chessPos* knightMovesArr = (chessPos*)malloc(8 * sizeof(chessPos));
    if (!knightMovesArr)
    {
        printf("Memory allocation failed.\n");
        exit(-1);
    }

    int phSize = 8;
    int curr = 0;
    processMoves(knightPos, &knightMovesArr, &curr, &phSize);
    *logSize = curr;

    return knightMovesArr;
}

chessPosArray*** validKnightMoves()    //this func creates and array of all the valid next positions
{
    int i = 0, j = 0;
    chessPos curr = { 0,0 };

    // Allocate memory for an array of chessPosArray pointers
    chessPosArray*** validMoves = (chessPosArray***)malloc(ROWS * sizeof(chessPosArray**));
    checkAllocation(validMoves);

    for (i = 0; i < ROWS; i++)
    {
        // Allocate memory for each chessPosArray
        validMoves[i] = (chessPosArray**)malloc(COLS * sizeof(chessPosArray*));
        for (j = 0; j < COLS; j++)
        {
            curr[0] = j + 'A';
            curr[1] = i + '1';

            // Allocate memory for the positions array in each chessPosArray
            validMoves[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));
            validMoves[i][j]->size = 0;
            validMoves[i][j]->positions = arrForKnightPos(curr, &(validMoves[i][j]->size));
        }
    }

    return validMoves;
}

bool isValidMove(chessPos optionalKnightPos)    //this func receives a position of knight and an optional position and checks if the optional is valid
{
    if (optionalKnightPos[1] < '1' || optionalKnightPos[1] > '5')
        return false;
    else if (optionalKnightPos[0] < 'A' || optionalKnightPos[0] > 'E')
        return false;
    else
        return true;
}

void createATable(chessPosList lst, int board[COLS][ROWS])   //this func gets a list and a board, and creates a table
{
    int count = 1;
    chessPosCell* current = lst.head;

    while (current != NULL) {
        int row = current->position[0] - 'A';
        int col = current->position[1] - '1';
        board[row][col] = count++;
        current = current->next;
    }
}

void printTable(chessPosList lst)    //this func recieves a list and prints a table
{
    int i, j, board[5][5] = { 0 };
    createATable(lst, board);
    printf("   1  2  3  4  5\n");
    for (i = 0; i < 5; i++)
    {
        printf("%c|", 'A' + i);

        for (j = 0; j < 5; j++)
        {
            if (board[i][j] == 0)
                printf("  |");
            else
                printf("%2d|", board[i][j]);
        }
        printf("\n");
    }
}

chessPos* chessPosToBoardPos(chessPos pos)     //this func recieves a position and convert the position to a board position
{
    chessPos* boardPos = (chessPos*)calloc(1, sizeof(chessPos));
    checkAllocation(boardPos);

    switch (pos[0])
    {
    case 'A':
        *(boardPos[0]) = 0;
        break;
    case 'B':
        *(boardPos[0]) = 1;
        break;
    case 'C':
        *(boardPos[0]) = 2;
        break;
    case 'D':
        *(boardPos[0]) = 3;
        break;
    case 'E':
        *(boardPos[0]) = 4;
        break;
    }

    *(boardPos[1]) = pos[1] - 1;
    return boardPos;
}

void checkAllocation(void* ptr)      //this func gets a pointer and checks if the allocation failed
{
    if (ptr == NULL)
    {
        printf("Allocation error\n");
        exit(-1);
    }
}

void displayBoard(chessPosCell* curr)     //this func gets a cell of the list and it removes duplicates in the list
{
    bool** board = (bool**)calloc(ROWS, sizeof(bool*));  // Allocate memory for ROWS number of pointers
    checkAllocation(board);

    for (int i = 0; i < ROWS; ++i)
    {
        board[i] = (bool*)calloc(COLS, sizeof(bool));    // Allocate memory for COLUMNS number of bools
        checkAllocation(board[i]);
    }

    chessPosCell* prev = curr;
    chessPosCell* toDelete = curr;

    while (curr != NULL)
    {
        chessPos* currChessPos = chessPosToBoardPos(curr->position);
        int currRow = *(currChessPos[0]);
        int currCol = *(currChessPos[1]) - '0';

        if (board[currRow][currCol]) //if the cell appeard in the list
        {
            toDelete = curr;
            curr = curr->next;
            prev->next = curr;
            free(toDelete);
        }
        else
        {
            board[currRow][currCol] = true;
            prev = curr;
            curr = curr->next;
        }
    }
}

void display(chessPosList* lst)  //this func recieves a pointer to a list and creates a board of the list and prints it
{
    displayBoard(lst->head);
    printTable(*lst);
}

bool isEmptyChessList(chessPosList lst)    //this func recieves a tree list and check if it's empty
{
    return (lst.head == NULL);
}


void freeArrForKnightPos(chessPos* knightMovesArr) {
    if (knightMovesArr != NULL) {
        free(knightMovesArr);
    }
}

void freeValidKnightMoves(chessPosArray*** validMoves) {
    if (validMoves != NULL) {
        for (int i = 0; i < ROWS; i++) {
            if (validMoves[i] != NULL) {
                for (int j = 0; j < COLS; j++) {
                    if (validMoves[i][j] != NULL) {
                        if (validMoves[i][j]->positions != NULL) {
                            free(validMoves[i][j]->positions);
                        }
                        free(validMoves[i][j]);
                    }
                }
                free(validMoves[i]);
            }
        }
        free(validMoves);
    }
}
