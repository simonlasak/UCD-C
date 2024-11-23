#include "functions.h"

//  function to insert list, each list is added to the very beginning(top) of the linked list.
void insertList(ListNodePtr *sPtr, char name[])
{
    ListNodePtr newPtr = malloc(sizeof(ListNode)); // allocates memory for the new list to be added
    if (newPtr != NULL)                            // if space is available
    {
        strcpy(newPtr->name, name); // copies name we want to insert
        newPtr->items = NULL;       // initially sets items to null, another function is used to insert items
        newPtr->nextPtr = NULL;

        ListNodePtr prev = NULL;
        ListNodePtr curr = *sPtr;
        while (curr != NULL) // iterates until it reaches end of linked list
        {
            prev = curr;
            curr = curr->nextPtr;
        }

        if (prev == NULL) // occurs when linked list is NULL
        {
            *sPtr = newPtr;
        }
        else
        { // adds newPtr to end of linked list.
            prev->nextPtr = newPtr;
        }
    }
    else
    {
        printf("error, no space available\n");
        fflush(stdout);
    }
}

// function to insert items, similar to insertList but with items.
void insertItem(ItemNodePtr *sPtr, char name[])
{
    ItemNodePtr newPtr = malloc(sizeof(ItemNode));
    if (newPtr != NULL) // space available
    {
        strcpy(newPtr->name, name); // copies name we want to insert
        newPtr->nextPtr = NULL;
        ItemNodePtr curr = *sPtr;
        ItemNodePtr prev = NULL;
        while (curr != NULL)
        {
            prev = curr;
            curr = curr->nextPtr;
        }
        if (prev == NULL)
        {
            *sPtr = newPtr;
        }
        else
        {
            prev->nextPtr = newPtr;
            newPtr->nextPtr = NULL;
        }
    }
    else
    {
        printf("Error: not inserted\n");
        fflush(stdout);
    }
}

// prints each list and it's items
void printList(ListNodePtr currentList)
{
    printf("\n");
    fflush(stdout);
    for (int i = 0; i < 25; i++)
    {
        printf("=");
        fflush(stdout);
    }

    while (currentList != NULL) // loops until it reaches end of board
    {
        printf("\n%s:\n", currentList->name); // prints list name
        fflush(stdout);
        ItemNodePtr currentItem = currentList->items; // points to first item of current list

        while (currentItem != NULL) // loops until it reaches end of items for the current list
        {
            printf("    %s\n", currentItem->name); // prints item name
            fflush(stdout);
            currentItem = currentItem->nextPtr; // moves to next item
        }
        currentList = currentList->nextPtr; // moves to next list
    }
    fflush(stdout);
    for (int i = 0; i < 25; i++)
    {
        printf("=");
        fflush(stdout);
    }
}

// loads a list from a given file name. (used for option 1 and 2 from menu)
void load(ListNodePtr *sPtr, char fileName[])
{
    FILE *fptr;
    char name[20]; // will be read from file (may be item or list)

    if ((fptr = fopen(fileName, "r")) == NULL)
    {
        printf("error opening file\n");
        fflush(stdout);
        return;
    }

    while (fgets(name, 20, fptr) != NULL) // loops until end of file
    {
        // removes new line character
        int size = strlen(name);
        if (name[size - 1] == '\n')
        {
            name[size - 1] = '\0';
        }

        // checks if name is an item or list, if it ends in : then its a list
        size = strlen(name);       //(get size again after removing new line character
        if (name[size - 1] == ':') // if : present then its a list
        {
            name[size - 1] = '\0';
            insertList(sPtr, name); // since its a list, use insert list function.
        }
        else
        {
            ListNodePtr curr = *sPtr;
            while (curr->nextPtr != NULL) // find the last entered list in the linked list to add its items.
            {
                curr = curr->nextPtr;
            }
            insertItem(&((curr)->items), name); // insertItem called with the last entered list.
        }
    }
    fclose(fptr);
}

void getFileName(char *fileNamePtr)
{
    FILE *fptr;
    printf("Enter filename:\n");
    fflush(stdout);
    fgets(fileNamePtr, 30, stdin);
    int size = strlen(fileNamePtr);

    // removes newline character
    if (fileNamePtr[size - 1] == '\n')
    {
        fileNamePtr[size - 1] = '\0';
    }

    while ((fptr = fopen(fileNamePtr, "r")) == NULL) // error handling if user enters wrong file name, asks them to re enter the name
    {
        printf("Error: could not open file %s\nPlease enter file name again\n",
               fileNamePtr);
        fflush(stdout);
        fgets(fileNamePtr, 30, stdin);
        int size = strlen(fileNamePtr);

        // removes newline character
        if (fileNamePtr[size - 1] == '\n')
        {
            fileNamePtr[size - 1] = '\0';
        }
    }
}

// functions for Edit List
ListNodePtr findList(ListNodePtr startingList)
{
    ListNodePtr currentList = startingList;
    char editName[20];
    printf("\nEnter the name of the list to edit: ");
    fflush(stdout);

    fgets(editName, 20, stdin);

    // remove new line
    int size = strlen(editName);
    if (editName[size - 1] == '\n')
    {
        editName[size - 1] = '\0';
    }
    // remove : if user enters it
    size = strlen(editName);
    if (editName[size - 1] == ':')
    {
        editName[size - 1] = '\0';
    }

    while (currentList != NULL) // loops until it reaches end of board
    {
        if (strcasecmp(currentList->name, editName) == 0) // used strcasecmp to have "Nick" and "nick" as equal names
        {
            return currentList;
        }
        currentList = currentList->nextPtr; // moves to next list
    }
    puts("\n -List not found, try again.-");
    fflush(stdout);
    return currentList;
}

void editItem(ListNodePtr listPointer)
{
    ItemNodePtr currentItem = listPointer->items; // points to first item of current list
    char itemToEdit[20];
    char newName[20];

    printf("Enter the name of the item to edit: ");
    fflush(stdout);
    fgets(itemToEdit, 20, stdin);
    int size = strlen(itemToEdit);

    if (itemToEdit[size - 1] == '\n')
    {
        itemToEdit[size - 1] = '\0';
    }

    while (currentItem != NULL) // loops until it reaches end of items for the current list
    {
        if (strcasecmp(currentItem->name, itemToEdit) == 0)
        {
            printf("Enter new name for item '%s': ", currentItem->name);
            fflush(stdout);
            fgets(newName, 20, stdin);
            newName[strlen(newName) - 1] = '\0';
            strcpy(currentItem->name, newName);
            printf("\n");
            fflush(stdout);
            return;
        }
        currentItem = currentItem->nextPtr; // moves to next item
    }
    puts("\n -Item not found, try again.- \n");
    fflush(stdout);
}

void addItem(ListNodePtr listPointer)
{
    char newItem[20];
    //get user input and remove the trailing whitespace
    printf("\nEnter the name of the new item: ");
    fflush(stdout);
    fgets(newItem, 20, stdin);
    newItem[strlen(newItem) - 1] = '\0';
    // call insertItem function with the pointer to the items pointer
    insertItem(&(listPointer->items), newItem);
}

void deleteItem(ListNodePtr listPointer)
{
    char itemToDelete[20];
    //get user input and remove the trailing whitespace
    printf("\nEnter the name of the item to delete: ");
    fflush(stdout);
    fgets(itemToDelete, 20, stdin);
    itemToDelete[strlen(itemToDelete) - 1] = '\0';

    ItemNodePtr currentItem = listPointer->items; // points to first item of current list
    ItemNodePtr nextItem = currentItem->nextPtr;  // points to next item of current list

    if ((strcmp(currentItem->name, itemToDelete)) == 0) // if match is found at the start of the list, the item pointer points to the next item
    {
        ItemNodePtr tempPtr = currentItem; // hold onto the node being removed
        listPointer->items = nextItem;     // de-thread the node
        free(tempPtr);                     // free the de-threaded node
        return;                            // return back to menu 3
    }

    while (nextItem != NULL) // loops until it reaches end of items for the current list
    {
        if (strcmp(nextItem->name, itemToDelete) == 0)
        {
            ItemNodePtr tempPtr = nextItem;
            currentItem->nextPtr = nextItem->nextPtr;
            free(tempPtr);
            return; // return back to menu 3
        }
        currentItem = nextItem; // moves to next item
        nextItem = nextItem->nextPtr;
    }
    // function did not return to menu 3, therefore the program did not find any match with the item to delete
    puts("\n -Item not found, try again.- \n");
    fflush(stdout);
}

void editList(ListNodePtr startingList)
{
    if(startingList == NULL)    //check if there is a list that can be edited
    {
        puts("\n -There is no list on your Board to edit-");
        fflush(stdout);
        return;
    }

    ListNodePtr listToEdit = findList(startingList); // find the pointer to the list we want to edit
    int choice = 1;                                  // choice of option from user

    if (listToEdit != NULL) // continue in the edit function only if the user input a list name that is on board
    {
        while (choice < 4 && choice > 0)
        {
            do
            {
                printf("Options:\n"
                       "1. Edit an item\n"
                       "2. Add a new item\n"
                       "3. Delete an item\n"
                       "4. Return to main menu\n"
                       "Enter your option: ");
                fflush(stdout);
                scanf("%d", &choice);
                getchar(); //consume newline character

                if (choice > 4 || choice < 1)
                {
                    printf("\n-Please enter a valid number between 1 and 4-\n");
                    fflush(stdout);
                }
            } while (choice > 4 || choice < 1);

            switch (choice)
            {
            case 1:
                editItem(listToEdit);
                break;
            case 2:
                addItem(listToEdit);
                break;
            case 3:
                deleteItem(listToEdit);
                break;
            default:
                break;
            }
        }
        printf("\nUpdated Board:");
        fflush(stdout);
        printList(startingList);
    }
}

//functions for Edit Board
void renameList(ListNodePtr pointerToFirst)
{
    if(pointerToFirst == NULL) //check if there even exists a list and advise user if not
    {
        puts("\n -There is no List to rename-");
        fflush(stdout);
        return;
    }

    ListNodePtr listToEdit = findList(pointerToFirst);  //one as the second argument because we need to get rid of the first character being skipped //check findList function

    //i had to get rid of the do while loop because it was just ruining the code for me keeping me in an infinite loop
    if(listToEdit == NULL)
    {
        return;
    }

    char newName[20];

    printf("Enter new name for list '%s': ", listToEdit->name);
    fflush(stdout);
    fgets(newName, 20, stdin);

    // remove new line
    int size = strlen(newName);
    if (newName[size - 1] == '\n')
    {
        newName[size - 1] = '\0';
    }
    // remove : if user enters it
    size = strlen(newName);
    if (newName[size - 1] == ':')
    {
        newName[size - 1] = '\0';
    }

    strcpy(listToEdit->name, newName);
}

void addList(ListNodePtr *sPtr)
{
    // ListNodePtr pointerToPointer = pointerToFirst;
    char newList[20];
    // get user input and remove the trailing whitespace
    printf("\nEnter the name of the new list: ");
    fflush(stdout);
    fgets(newList, 20, stdin);
    newList[strlen(newList) - 1] = '\0';
    // if user inputs semicolon delete it
    if (newList[strlen(newList) - 1] == ':')
    {
        newList[strlen(newList) - 1] = '\0';
    }
    // call insertList function with the list pointer
    insertList(sPtr, newList);
}

void deleteList(ListNodePtr *sPtr)
{
    if(*sPtr == NULL)   //check if there even exists a list and advise user if not
    {
        puts("\n -There is no List to delete-");
        fflush(stdout);
        return;
    }

    char listToDelete[20];
    //get user input and remove the trailing whitespace
    printf("\nEnter the name of the list to delete: ");
    fflush(stdout);
    fgets(listToDelete, 20, stdin);

    listToDelete[strlen(listToDelete) - 1] = '\0';

    if (listToDelete[strlen(listToDelete) - 1] == ':')
    {
        listToDelete[strlen(listToDelete) - 1] = '\0';
    }

    ListNodePtr currentList = *sPtr; // points to first item of current list
    ListNodePtr nextList = currentList->nextPtr;    // points to next item of current list

    if((strcmp((*sPtr)->name, listToDelete))==0)    //if match is found at the start of the list, the item pointer points to the next item
    {
        ListNodePtr tempPtr = *sPtr;              //hold onto the node being removed
        *sPtr = (*sPtr)->nextPtr;                 //de-thread the node
        free(tempPtr);                                  //free the de-threaded node
        return;                                         //return back to menu 4
    }

    while (nextList != NULL) // loops until it reaches end of items for the current list
    {
        if (strcmp(nextList->name, listToDelete) == 0)
        {
            currentList->nextPtr = nextList->nextPtr;
            free(nextList);
            return;                                     //return back to menu 4
        }
        currentList = nextList; // moves to next item
        nextList = nextList->nextPtr;
    }
    //function did not return to menu 4, therefore the program did not find any match with the item to delete
    puts("\n -List not found, try again.- \n");
    fflush(stdout);
}

void editBoard(ListNodePtr *pointerToFirst)
{
    int choice = 1; // choice of option from user

    while (choice < 4 && choice > 0)
    {
        do
        {
            printf("\nOptions:\n"
                   "1. Edit the name of a list\n"
                   "2. Add a new list\n"
                   "3. Delete a list\n"
                   "4. Return to main menu\n"
                   "Enter your option: ");
            fflush(stdout);
            scanf("%d", &choice);
            getchar();
            if (choice > 4 || choice < 1)
            {
                printf("\n-Please enter a valid number between 1 and 4-\n");
                fflush(stdout);
            }
        } while (choice > 4 || choice < 1);

        switch (choice)
        {
            case 1:
                renameList(*pointerToFirst);
                break;
            case 2:
                addList(pointerToFirst);
                break;
            case 3:
                deleteList(pointerToFirst);
                break;
            default:
                break;
        }
    }
    printf("\nUpdated Board:");
    fflush(stdout);
    printList(*pointerToFirst);
}

void saveBoard(ListNodePtr pointerToFirst)
{
    ListNodePtr currentList = pointerToFirst;

    if(pointerToFirst == NULL)  //check if there is at least one list on the board
    {
        puts("\n -There is no Board that can be saved-");
        fflush(stdout);
        return;
    }

    char fileName[30];
    printf("Enter filename (.txt only): ");
    fflush(stdout);
    fgets(fileName, 30, stdin);
    fileName[strlen(fileName) - 1] = '\0';

    FILE *fptr;
    if( (fptr = fopen(fileName, "w")) == NULL)  //open file and check if it could be created for writing
    {
        puts("\nThe file could not be saved successfully :-(");
        fflush(stdout);
        return;
    }

    else{
        while (currentList != NULL) // loops until it reaches end of board
        {
            fputs(currentList->name, fptr);
            fputs(":\n", fptr);
            ItemNodePtr currentItem = currentList->items; // points to first item of current list

            while (currentItem != NULL) // loops until it reaches end of items for the current list
            {
                fputs(currentItem->name, fptr);
                fputs("\n", fptr);
                currentItem = currentItem->nextPtr; // moves to next item
            }
            currentList = currentList->nextPtr; // moves to next list
        }
    }
    puts("Board saved successfully!");          //tell user that their board has been saved
    fflush(stdout);
    fclose(fptr);                               //close the file
}

