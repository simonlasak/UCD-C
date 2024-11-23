
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//for items
struct itemNode{
    char name[20];
    struct itemNode *nextPtr;
};

//for lists
struct listNode
{
    char name[20];
    struct itemNode *items;
    struct listNode *nextPtr;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

typedef struct itemNode ItemNode;
typedef ItemNode *ItemNodePtr;

//function declarations
void insertList(ListNodePtr *sPtr, char name[]);
void insertItem(ItemNodePtr *sPtr, char name[]);
void printList(ListNodePtr currentList);
void load(ListNodePtr *sPtr, char fileName[]);
void getFileName(char * fileNamePtr);
ListNodePtr findList(ListNodePtr startingList);
void editItem(ListNodePtr listPointer);
void addItem(ListNodePtr listPointer);
void deleteItem(ListNodePtr listPointer);
void editList(ListNodePtr startingList);
void renameList(ListNodePtr pointerToFirst);
void addList(ListNodePtr *sPtr);
void deleteList(ListNodePtr *sPtr);
void editBoard(ListNodePtr *pointerToFirst);
void saveBoard(ListNodePtr pointerToFirst);

#endif /* FUNCTIONS_H_ */
