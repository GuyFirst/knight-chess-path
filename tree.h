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
void 		findKnightPathCoveringAllBoardRec(chessPosList* lst, treeNode* root, int* count); 
void 		removeNodeFromEndList(chessPosList* lst); 
chessPosList* 	findKnightPathCoveringAllBoard(pathTree* path_tree);//finds a path that covers the whole board
void 		insertNodeToEndList(treeNodeList* lst, treeNodeListCell* newTail); //inserts a nodeList to the end of the list
void 		makeEmptyList(treeNodeList* lst);
bool 		isEmptyTreeList(treeNodeList lst); 
void 		insertNodeToStartList(chessPosList* lst, chessPosCell* newHead);
treeNodeListCell*createNewListNode(treeNode* node, treeNodeListCell* next); 
treeNode* 	createTreeNode(chessPos pos, treeNodeList lst); 
void 		findAllPossibleKnightPathsRec(bool forbidden[ROWS][COLS], treeNode* root, chessPosArray*** chessBoard); 
pathTree 	findAllPossibleKnightPaths(chessPos* startingPosition); 
treeNodeListCell* createNewTreeNodeListCell(treeNode* addNode); 
treeNode* 	  createNewTreeNode(chessPos* position); 
void 		  addChildToTreeNode(treeNode* parent, treeNode* child); 
treeNodeListCell* makeListFromArrRec(chessPos* arr, int logSize, treeNodeList* lst); 
treeNodeList* 	  makeListFromArr(chessPos pos, chessPosArray*** chessBoard);
void 		  freeTree(pathTree* tr); 
void 		  freeTreeRec(treeNode* node); 
