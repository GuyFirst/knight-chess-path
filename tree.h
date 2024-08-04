#pragma once
#include "allInclude.h"

//DEFINITIONS OF TREE AND LIST IN THE TREE//
typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNodeList {
	treeNodeListCell* head;
	treeNodeListCell* tail;
} treeNodeList;

typedef struct _treeNode {
	chessPos position;
	treeNodeList next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;


typedef struct _pathTree {
	treeNode* root;
} pathTree;



//------------ FUNC DECLARATIONS ------------//
void findKnightPathCoveringAllBoardRec(chessPosList* lst, treeNode* root, int* count); //finds a path that covers the whole board
void removeNodeFromEndList(chessPosList* lst); //removes node from the end of the list
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);//finds a path that covers the whole board
void insertNodeToEndList(treeNodeList* lst, treeNodeListCell* newTail); //inserts a nodeList to the end of the list
void makeEmptyList(treeNodeList* lst);//makes the list empty
bool isEmptyTreeList(treeNodeList lst); // checks if the list is empty
void insertNodeToStartList(chessPosList* lst, chessPosCell* newHead); //it inserts the node to the beginning of the list
treeNodeListCell* createNewListNode(treeNode* node, treeNodeListCell* next); //creates a new list node
treeNode* createTreeNode(chessPos pos, treeNodeList lst); //creates a tree node
void findAllPossibleKnightPathsRec(bool forbidden[ROWS][COLS], treeNode* root, chessPosArray*** chessBoard); //finds all the possible paths recursively
pathTree findAllPossibleKnightPaths(chessPos* startingPosition); //the main func that builds a tree to describe a knight path in the board
treeNodeListCell* createNewTreeNodeListCell(treeNode* addNode); //creates a new treeNodeListCell
treeNode* createNewTreeNode(chessPos* position); //creates a new tree node
void addChildToTreeNode(treeNode* parent, treeNode* child); // add leaf to tree
treeNodeListCell* makeListFromArrRec(chessPos* arr, int logSize, treeNodeList* lst); //makes a list from the given array recursively
treeNodeList* makeListFromArr(chessPos pos, chessPosArray*** chessBoard); //make a list from the given array
void freeTree(pathTree* tr); //frees the tree
void freeTreeRec(treeNode* node); //frees the tree recursively