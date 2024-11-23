#include "functions.h"

int main(void) {
	ListNodePtr startList = NULL; // start pointer for lists

	int choice = 0; // stores users choice
	char fileName[60] = "eclipseList.txt"; // stores file name
	while (choice != 6)             // runs while user does not request to quit
	{
		do {
			printf("\nMenu:\n"
					"1.Display board\n"
					"2.Load board from a file\n"
					"3.Edit list\n"
					"4.Edit board\n"
					"5.Save board to a file\n"
					"6.Quit\n"
					"Please enter your choice(1-6)\n-> ");
			fflush(stdout);
			scanf("%d", &choice);
			getchar(); // takes in new line character

			if (choice <= 0 || choice >= 7) // user has given invalid input
					{
				printf("\n-Please enter a valid number between 1 and 6-\n");
				fflush(stdout);
			}
		} while (choice <= 0 || choice >= 7); // continues to ask for input until user inputs number between 1 and 6

		switch (choice) {
		case 1:
			startList = NULL;
			load(&startList, fileName); // loads board from eclipseList.txt which is stored in same directory as src folder.
			printList(startList);                // prints board
			break;
		case 2:
			startList = NULL;
			getFileName(fileName); //get the name of the file
			load(&startList, fileName); //loads board
			break;
		case 3:
			editList(startList);        //option 3 = edit list
			break;
		case 4:
			editBoard(&startList);       //option 4 = edit board
			break;
		case 5:
			saveBoard(startList);        //option 5 = save board
			break;
		default:                        //option 6 = quit program

			printf("\nExiting program...\n");
			printf("    _    _\n");
			printf("   /=\"\"\"/=\\\n");
			printf("  (=(0_0 |=)__\n");
			printf("   \\_\\ _/_/   )\n");
			printf("     /_/   _  /\\\n");
			printf("    |/ |\\ || |\n");
			printf("       ~ ~  ~\n");
			fflush(stdout);
			return 0;
			break;

		}
	}
}

