#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINE_LENGTH 180
#define MAX_NUM_OF_TASKS 10

//initialise enums and structs outside main function to access them from each part of code
enum month {january,february,march,april,may,june,july,august,september,october,november,december}; // {0,1,2,3,4,5,6,7,8,9,10,11}
enum state {edit, test, quit};

struct task{
	char name[30];
	int start_month;
	int end_month;
    int numOfDependencies;
	int dependencies[9];
};

//header function prints out the months of the Gantt chart in a formatted matter
void header(void)
{
	printf("\n");
	fflush(stdout);
    for(int i = 0; i < LINE_LENGTH; i++) {
        printf("_");
        fflush(stdout);
    }

    printf("\n%30c", '|');
    fflush(stdout);
    enum month index;

    for (index = 0; index<12; index++)
    {
        switch(index){
		    case(january):
			    printf("%9s ", "January");
		    	fflush(stdout);
			    break;
		    case(february):
			    printf("%9s ", "February");
		    	fflush(stdout);
			    break;
		    case(march):
			    printf("%7s   ", "March");
		    	fflush(stdout);
		    	break;
		    case(april):
			    printf("%7s   ", "April");
		    fflush(stdout);
			    break;
		    case(may):
			    printf("%6s    ", "May");
		    fflush(stdout);
			    break;
            case(june):
			    printf("%7s   ", "June");
            fflush(stdout);
			    break;
            case(july):
			    printf("%7s   ", "July");
            fflush(stdout);
			    break;
            case(august):
			    printf("%8s  ", "August");
            fflush(stdout);
			    break;
            case(september):
			    printf("%10s", "September");
            fflush(stdout);
			    break;
            case(october):
			    printf("%9s ", "October");
            fflush(stdout);
			    break;
            case(november):
			    printf("%9s ", "November");
            fflush(stdout);
			    break;
            case(december):
			    printf("%9s ", "December");
            fflush(stdout);
			    break;

		    default:
			    break;
        }
        putchar('|');
        fflush(stdout);
    }
    printf("%15s\n", "Dependencies");
    fflush(stdout);
    for(int x = 0; x<LINE_LENGTH; x++)
    {
    	printf("-");
    	fflush(stdout);
    }
}

//body function takes in the tasks struct and number of tasks to determine how many rows it should have
void body (struct task tasks[], int numberoftasks)
{
	for (int i = 0; i<numberoftasks; i++)
    {
        printf("\n%s%*c", (tasks[i].name), 30 - strlen(tasks[i].name), '|');        //the asterisk in the format specifier lets us put in a variable number of spaces before the character
        fflush(stdout);
        for(int y = 0; y<12;y++)
		{
			if (y <= (tasks[i].end_month -1) && y >= (tasks[i].start_month -1))     //if the column is marked in between start and end month of the dependency mark it XXX
            {
                printf("%6s    |", "XXX");
                fflush(stdout);
            }
			else                                                                    //if not just put in 10 whitespaces and the separation line
            {
                printf("%11c", '|');
                fflush(stdout);
            }
		}
        for(int z = 0; z < tasks[i].numOfDependencies; z++)                         //print out the dependencies of the task
		{
			printf("%2d", tasks[i].dependencies[z]+1);
            fflush(stdout);
		}
        printf("\n");
        fflush(stdout);
        for(int x = 0; x<LINE_LENGTH; x++)                                         //this is the line under the task row 
        {
            printf("-");
            fflush(stdout);
        }
    }
}

//function input takes input from the user if they decide to not print the sample gantt
int input(struct task allTasks[])
{
    int numberOfTasks;

    do
    {                                                                   //take in the number of tasks, however only up to 10 tasks can be input
        printf("How many tasks would you like to add ? (1-10)\n");
        fflush(stdout);
        scanf("%d", &numberOfTasks);

        if (numberOfTasks < 1 || numberOfTasks > 10)
        {
            printf("\nThe number of tasks must be in range 1 - 10!\n");
            fflush(stdout);
        }

    }while(numberOfTasks < 1 || numberOfTasks > 10);

    //enter the task name 
    for (size_t i = 0; i < numberOfTasks; i++)      
    {
        printf("\nPlease enter the task name\n");
        fflush(stdout);
        scanf("%29s", (allTasks[i].name));

        do      //choose a start month, it has to be in range 1-12
        {
            printf("Start month (1-12):\n");
            fflush(stdout);
            scanf("%d", &allTasks[i].start_month);

            if (allTasks[i].start_month < 1 || allTasks[i].start_month > 12)
            {
                printf("\nThe start month must be in range 1 - 12!\n");
                fflush(stdout);
            }
        }while(allTasks[i].start_month < 1 || allTasks[i].start_month > 12);

        do      //enter end month, it has to be in range start.month - 12
        {
            printf("End month (%d-12):\n", allTasks[i].start_month);
            fflush(stdout);
            scanf("%d", &allTasks[i].end_month);
            
            if (allTasks[i].end_month < allTasks[i].start_month || allTasks[i].end_month > 12)
            {
                printf("\nThe end month must be in range %d - 12!\n", allTasks[i].start_month);
                fflush(stdout);
            }
        }while (allTasks[i].end_month < allTasks[i].start_month || allTasks[i].end_month > 12);

        do      //the number of dependencies a task can have is only up to number of tasks -1
        {
            printf("Enter how many dependencies this task has\n");
            fflush(stdout);
            scanf("%d", &allTasks[i].numOfDependencies);
            
            if (allTasks[i].numOfDependencies < 0 || allTasks[i].numOfDependencies > numberOfTasks-1)
            {
                printf("\nThe number of dependent tasks must be in range 0 - %d!\n", numberOfTasks-1);
                fflush(stdout);
            }
        } while (allTasks[i].numOfDependencies < 0 || allTasks[i].numOfDependencies > numberOfTasks-1);
        


        for (size_t j = 0; j<allTasks[i].numOfDependencies; j++)
        {
            do      // the dependent tasks have to be in range of the number of tasks 
            {
                printf("Enter dependent task\n");
                fflush(stdout);
                scanf("%d", &allTasks[i].dependencies[j]);

                if(allTasks[i].dependencies[j] < 1 || allTasks[i].dependencies[j] > numberOfTasks)
                    {printf("\nThe dependent task must be in range 1 - %d!\n", numberOfTasks);
                    fflush(stdout);}
            } while(allTasks[i].dependencies[j] < 1 || allTasks[i].dependencies[j] > numberOfTasks);
            allTasks[i].dependencies[j]--;
        }
    }
    return numberOfTasks;
}

//this function initialises the pre-made sample task list and copies it to the main task struct then calls the print body function
int printSample(struct task allTasks[])
{
    int nTasks = 10;                                            //number of tasks
    struct task sampleTasks[10] = {{"Planning", 1, 2, 0, {0}},
                                {"Projecting", 2, 3, 1, {0}},
                                {"Approval_for_Preparation", 2,3, 1, {1}},
                                {"Recruitment", 3, 4, 1, {2}},
                                {"Teambuilding", 3, 4, 1, {3}},
                                {"Scheming", 4, 5, 2, {2,3}},
                                {"Software_Development", 5, 8, 1, {5}},
                                {"Prototype", 8, 8, 1, {6}},
                                {"Software_implementation", 8, 10, 2, {6,7}},
                                {"Marketing", 11,12, 1, {8}}};

    memcpy(allTasks, sampleTasks, sizeof(sampleTasks));         //use memcpy to copy sample tasks to alltasks struct
    body(allTasks, nTasks);                                     //print the body of the chart with sample tasks
    return nTasks;
}

//function to edit the exact task
void editTask(struct task allTasks[], int numberoftasks, int taskNumber)
{
    char newName[30];       

    printf("Please enter the new task name or write its old one\n");
    fflush(stdout);
    scanf("%29s", newName);                     //take the new name of the task from user 
    strcpy(allTasks[taskNumber].name, newName); //copy the new name to the struct task
    //the rest of the test is almost identical to the input function
    do
    {
        printf("Start month (1-12):\n");
        fflush(stdout);
        scanf("%d", &allTasks[taskNumber].start_month);
            
        if (allTasks[taskNumber].start_month < 1 || allTasks[taskNumber].start_month > 12)
        {
            printf("\nThe start month must be in range 1 - 12!\n");
            fflush(stdout);
        }
    }while (allTasks[taskNumber].start_month < 1 || allTasks[taskNumber].start_month > 12);

    do
    {
        printf("End month (1-12):\n");
        fflush(stdout);
        scanf("%d", &allTasks[taskNumber].end_month);

        if (allTasks[taskNumber].end_month < 1 || allTasks[taskNumber].end_month > 12)
        {
            printf("\nThe end month must be in range 1 - 12!\n");
            fflush(stdout);
        }
    }while (allTasks[taskNumber].end_month < 1 || allTasks[taskNumber].end_month > 12);

    do
    {
        printf("Enter how many dependencies this task has\n");
        fflush(stdout);
        scanf("%d", &allTasks[taskNumber].numOfDependencies);

        if (allTasks[taskNumber].numOfDependencies < 0 || allTasks[taskNumber].numOfDependencies > numberoftasks)
        {
            printf("\nThe number of dependent tasks must be in range 0 - %d!\n", numberoftasks);
            fflush(stdout);
        }

    }while(allTasks[taskNumber].numOfDependencies < 0 || allTasks[taskNumber].numOfDependencies > numberoftasks);

    for (size_t i = 0; i<allTasks[taskNumber].numOfDependencies; i++)
    {
        do
        {
            printf("Enter dependent task\n");
            fflush(stdout);
            scanf("%d", &allTasks[taskNumber].dependencies[i]);

            if (allTasks[taskNumber].dependencies[i] < 1 || allTasks[taskNumber].dependencies[i] > numberoftasks)
            {printf("\nThe dependent task must be in range 1 - %d!\n", numberoftasks);
            fflush(stdout);}
        } while (allTasks[taskNumber].dependencies[i] < 1 || allTasks[taskNumber].dependencies[i] > numberoftasks);

        allTasks[taskNumber].dependencies[i]--;
    }

    system("cls"); //This does not work in eclipse, but should clear the screen
    //print the new updated gantt chart
    printf("This is your new Gantt Chart:\n"); 
    fflush(stdout);
    header();
    body(allTasks, numberoftasks);
}

//this function is vital to determine which task the user wants to edit by matching the name entered with the list of tasks
void decideWhichTaskToEdit(struct task allTasks[], int numberoftasks)
{
    char taskChange[30];
    printf("\nPlease enter the task name you wish to change exactly\n");
    fflush(stdout);
    scanf("%29s", taskChange);

    //initialize the iteration index i to have access to it even after the loop is exited
    //this loop goes through the list of task names and tries to match the string input from terminal to each of them
    size_t i = 0;
    for (; i< numberoftasks; i++)
    {
        if (strcmp(allTasks[i].name, taskChange) == 0)      
        {
            editTask(allTasks, numberoftasks, i);       //if the string matches to some of the tasks, call the edit function with the index i being the task number to edit
            break;
        }
    }

    //the interation has reached the end, that means there was no task matching the string entered
    //this goes back to the menu option that lets the user choose what he wants to do
    if (i == numberoftasks)
    {
        printf("\nNo such task found!\n");
        fflush(stdout);
    }
}

//this function recursively goes through the dependency path and prints whether there is a possibility of a circular dependency
void printDependentTasks(struct task allTasks[], int taskNumber, int visitedTasks[]) {
	printf("%d -> ", taskNumber+1);		//print visited task
	fflush(stdout);
	visitedTasks[taskNumber]=1;			//mark as visited

	for (int i =0; i < allTasks[taskNumber].numOfDependencies; i++) {		//base case
		int dependentTaskNumber = allTasks[taskNumber].dependencies[i];		//setup for recursive call

		if (visitedTasks[dependentTaskNumber] == 0) {						//recursive call
			printDependentTasks(allTasks, dependentTaskNumber, visitedTasks);

		}
		else {
			printf("(!!!!!!!!!! warning potential circular dependency !!!!!!!!!!)\n");
            fflush(stdout);
		}
	}

}


int main(){
    //initialise the struct of tasks and number of tasks
    struct task allTasks[10];
    int numberOfTasks;

    //prompt the user to decide if he wants to see the example or not
    printf("Welcome to the Gantt Generator\nWould you like to use the test example (yes) or create your on Gantt from scratch (no)?\n");
    fflush(stdout);
    char decisionForExample[4];
    scanf("%3s", decisionForExample);

    //three if else statements to determine if user input a valid answer
    if (strcasecmp("yes", decisionForExample) == 0)
    {
        header();
        numberOfTasks = printSample(allTasks);
    }
    else if(strcasecmp("no", decisionForExample) == 0){
        numberOfTasks = input(allTasks);
        header();
        body(allTasks, numberOfTasks);
    }
    else{
        printf("Try again, but type yes/no");   
        fflush(stdout);
        return 0;
    }

    int visitedTasks[MAX_NUM_OF_TASKS] = {0};
    int taskNumber;


    enum state GanttStatus;             //initialise the state of the actions the user wants to do with the gantt
    while(GanttStatus != quit)          //keep the user in menu until he doesn't type quit
    {
        char stateString[5];

        do
        {   //keep the user in a loop until he types in a valid action either edit, test or quit
            printf("\nIf you wish to edit the Gantt please type \"edit\" / If you wish to run a test, type \"test\" or to\n"
            "exit, type \"quit\" and then press enter to execute your option.\n");
            fflush(stdout);
            scanf("%4s", stateString);

            if ((strcasecmp("edit", stateString) != 0) && (strcasecmp("test", stateString) != 0) && (strcasecmp("quit", stateString) != 0))
            {
                printf("\nNo such prompt as the one provided.");
                fflush(stdout);
            }
        } while ((strcasecmp("edit", stateString) != 0) && (strcasecmp("test", stateString) != 0) && (strcasecmp("quit", stateString) != 0));
        


        if (strcasecmp("edit", stateString) == 0)   //if the user opts for edit, call function to decide which task to edit that eventually calls the edit function and sets the state of the enum to edit
        {
            decideWhichTaskToEdit(allTasks, numberOfTasks);
            GanttStatus = edit;
        }
        else if (strcasecmp("test", stateString) == 0)  //the same as edit but with test
        {
        	printf("Enter a Task Number to test: ");
        	fflush(stdout);
        	scanf("%d", &taskNumber);

        	if (taskNumber > 0 && taskNumber <= numberOfTasks) {
        		for(int i = 0; i < MAX_NUM_OF_TASKS; i++) {
        		        visitedTasks[i] = 0;						//reset visitedTasks[]
        		    }
        		printDependentTasks(allTasks, taskNumber - 1, visitedTasks);
        		GanttStatus = test;
        	}
        	else {
        		printf("Invalid task number.\n");
                fflush(stdout);
        	}
        }
        else{
        	printf("   _____  ____   ____  _____  ______     ________ \n");
        	printf("  / ____|/ __ \\ / __ \\|  __ \\|  _ \\ \\   / /  ____|\n");
        	printf(" | |  __| |  | | |  | | |  | | |_) \\ \\_/ /| |__   \n");
        	printf(" | | |_ | |  | | |  | | |  | |  _ < \\   / |  __|  \n");
        	printf(" | |__| | |__| | |__| | |__| | |_) | | |  | |____ \n");
        	printf("  \\_____|\\____/ \\____/|_____/|____/  |_|  |______|\n");
        	exit(0);
            GanttStatus = quit; //if user opts for quit, print ascii art and terminate the program
        }
    }
    return 0;
}
