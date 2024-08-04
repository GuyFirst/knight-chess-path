#include "allInclude.h"

void findKnightPathCoveringAllBoardRec(chessPosList* lst, treeNode* root, int* count) //this func gets a pointer to a list, a root, and pointer to counter
{                                                                                     //then it finds a path that covers the whole board
    chessPosCell* cell = (chessPosCell*)malloc(sizeof(chessPosCell));
    checkAllocation(cell);

    cell->position[0] = root->position[0];
    cell->position[1] = root->position[1];
    cell->next = NULL;

    insertNodeToEndList(lst, cell);

    (*count)++;

    if (*count == (ROWS) * (COLS))
        return lst;

    if (isEmptyTreeList(root->next_possible_positions))
    {
        (*count)--;
        removeNodeFromEndList(lst);
        return;
    }
    else
    {
        treeNodeListCell* curr = root->next_possible_positions.head;
        while (curr != NULL) {
            findKnightPathCoveringAllBoardRec(lst, curr->node, count);

            if (*count == (ROWS) * (COLS))
                return;
            curr = curr->next;
        }
        (*count)--;
        removeNodeFromEndList(lst);
    }

}

void removeNodeFromEndList(chessPosList* lst)    //this func recieves a list and removes node from the end of the list
{
    if (lst->head == NULL)
        return;

    if (lst->head == lst->tail)
    {
        free(lst->head);
        lst->head = lst->tail = NULL;
        return;
    }

    chessPosCell* current = lst->head;
    while (current->next != lst->tail)
        current = current->next;

    free(lst->tail);
    current->next = NULL;
    lst->tail = current;
}

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)   //this func gets a tree and then finds a path that covers the whole board
{
    int count = 0;
    chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
    checkAllocation(lst);
    makeEmptyList(lst);

    findKnightPathCoveringAllBoardRec(lst, path_tree->root, &count);
    return lst;
}

void insertNodeToEndList(treeNodeList* lst, treeNodeListCell* newTail)   //this func recieves a list and a pointer to tail,
{                                                                        //then it inserts node to the end of the list
    if (isEmptyTreeList(*lst))
    {
        lst->head = lst->tail = newTail;
    }
    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

void makeEmptyList(treeNodeList* lst)     //this func receives a list and empty it
{
    lst->head = lst->tail = NULL;
}

bool isEmptyTreeList(treeNodeList lst)    //this func recieves a tree list and check if it's empty
{
    return (lst.head == NULL);
}

void insertNodeToStartList(chessPosList* lst, chessPosCell* newHead)   //this func receives a pointer to a list and a pointer to a list head
{                                                                      //then, it inserts the node to the beginning of the list
    if (isEmptyChessList(*lst))
    {
        lst->head = lst->tail = newHead;
    }
    else
    {
        newHead->next = lst->head;
        lst->head = newHead;
    }
}

treeNodeListCell* createNewListNode(treeNode* node, treeNodeListCell* next)    //this func gets a pointer to node, and pointer to next list cell
{                                                                              //then it creates a new list node
    treeNodeListCell* cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    checkAllocation(cell);
    cell->node = node;
    cell->next = next;
    return cell;

}

treeNode* createTreeNode(chessPos pos, treeNodeList lst)             //this func gets a pos, and a list, then it creates a tree node
{
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
    checkAllocation(node);
    node->position[0] = pos[0];
    node->position[1] = pos[1];
    node->next_possible_positions = lst;
    return node;

}

void findAllPossibleKnightPathsRec(bool forbidden[ROWS][COLS], treeNode* root, chessPosArray*** chessBoard)     //this func gets a board and pointer to a root and finds all the possible paths
{
    int currRow = root->position[0] - 'A';
    int currColumn = root->position[1] - '1';

    // Check if current position is forbidden
    if (forbidden[currRow][currColumn]) {
        return;
    }

    // Create a list of next possible positions
    treeNodeList* currentList = makeListFromArr(root->position, chessBoard);
    root->next_possible_positions.head = currentList->head;
    root->next_possible_positions.tail = currentList->tail;

    // Mark current position as forbidden in a new array
    bool newForbidden[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            newForbidden[i][j] = forbidden[i][j];
        }
    }

    newForbidden[currRow][currColumn] = true;


    // Clean up invalid positions from next_possible_positions list
    treeNodeListCell* prev = NULL;
    treeNodeListCell* cell = root->next_possible_positions.head;

    while (cell != NULL) {
        int row = cell->node->position[0] - 'A';
        int col = cell->node->position[1] - '1';

        if (forbidden[row][col]) {
            treeNodeListCell* toDelete = cell;
            if (cell == root->next_possible_positions.head) {
                root->next_possible_positions.head = cell->next;
            }
            else {
                prev->next = cell->next;
            }

            if (cell == root->next_possible_positions.tail) {
                root->next_possible_positions.tail = prev;
            }

            cell = cell->next;
            free(toDelete);
        }
        else {
            prev = cell;
            cell = cell->next;
        }
    }

    // Recursively find paths for each valid next position
    treeNodeListCell* currSubRoot = root->next_possible_positions.head;
    while (currSubRoot != NULL) {
        findAllPossibleKnightPathsRec(newForbidden, currSubRoot->node, chessBoard);
        currSubRoot = currSubRoot->next;
    }

    // Clean up currentList
    free(currentList);
}

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)   //this func recieves a pointer to a position and it finds all the possible paths for the knight
{
    pathTree tree;
    bool haveWeBeenHere[ROWS][COLS] = { false };
    tree.root = createNewTreeNode(startingPosition);
    int count = 0;
    chessPosArray*** chessBoard = validKnightMoves();

    findAllPossibleKnightPathsRec(haveWeBeenHere, tree.root, chessBoard);
    freeValidKnightMoves(chessBoard);

    return tree;
}

treeNodeListCell* createNewTreeNodeListCell(treeNode* addNode)    //this func recieves a pointer to a treeNode and creates a list cell 
{
    treeNodeListCell* newCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    checkAllocation(newCell);
    newCell->node = addNode;
    newCell->next = NULL;
    return newCell;
}

treeNode* createNewTreeNode(chessPos* position)        //this fung recieves a pointer to a position and creates a new tree node
{
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    checkAllocation(newNode);
    newNode->position[0] = (*position)[0];
    newNode->position[1] = (*position)[1];
    newNode->next_possible_positions.head = NULL;
    newNode->next_possible_positions.tail = NULL;

    return newNode;
}


void addChildToTreeNode(treeNode* parent, treeNode* child)    //this func gets 2 pointers to treeNodes: a parent and a child, then it adds the child to the tree
{
    treeNodeListCell* newCell = createNewTreeNodeListCell(child);

    if (parent->next_possible_positions.tail)
    {
        parent->next_possible_positions.tail->next = newCell;
    }
    else
    {
        parent->next_possible_positions.head = newCell;
    }
    parent->next_possible_positions.tail = newCell;
}


treeNodeListCell* makeListFromArrRec(chessPos* arr, int logSize, treeNodeList* list)  //this func gets an array, a size, and a pointer to a list 
{                                                                                     //then it makes a list from the given array
    if (!logSize)
    {
        return NULL;
    }
    else
    {
        for (int i = 0; i < logSize; i++)
        {
            treeNodeListCell* cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
            checkAllocation(cell);
            cell->node = (treeNode*)malloc(sizeof(treeNode));
            checkAllocation(cell->node);
            cell->node->position[0] = arr[i][0];
            cell->node->position[1] = arr[i][1];
            cell->node->next_possible_positions.head = NULL;
            cell->node->next_possible_positions.tail = NULL;
            insertNodeToEndList(list, cell);

            cell->next = makeListFromArrRec(++arr, --logSize, list);
            return cell;
        }

    }
}

treeNodeList* makeListFromArr(chessPos pos, chessPosArray*** chessBoard)   //this func recieves a position and make a list from the given array
{

    int currRow = pos[0] - 'A';
    int currColumn = pos[1] - '1';

    chessPosArray* arr = chessBoard[currColumn][currRow];


    treeNodeList* lst = (treeNodeList*)malloc(sizeof(treeNodeList));
    checkAllocation(lst);
    makeEmptyList(lst);
    treeNodeListCell* head = makeListFromArrRec(arr->positions, arr->size, lst);
    lst->head = head;
    treeNodeListCell* node = head;
    treeNodeListCell* prev = head;

    while (node != NULL)
    {
        prev = node;
        node = node->next;
    }

    lst->tail = prev;
    return lst;
}

void freeTree(pathTree* tr)     //this func recieves a tree and frees it
{
    if (tr->root != NULL)
    {
        freeTreeRec(tr->root);
    }
}

void freeTreeRec(treeNode* node)    //this func recieves a node and frees it
{
    if (node->next_possible_positions.head == NULL && node->next_possible_positions.tail == NULL)
        free(node);
    else
    {
        treeNodeListCell* curr = node->next_possible_positions.head;
        while (curr != NULL)
        {
            treeNodeListCell* next = curr->next;
            freeTreeRec(curr->node);
            free(curr);
            curr = next;
        }
        node->next_possible_positions.head = NULL;
        node->next_possible_positions.tail = NULL;
        free(node);
    }
}

