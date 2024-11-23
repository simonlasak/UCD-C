/*
 * sortAndShuffle.c
 *
 *  Created on: 23 Feb 2024
 *      Author: imonl
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sortAndShuffle.h"
#define MAX_ARTISTS 4
#define MAX_SONGS 3
#define MAX_LENGTH 80
#define MIN_DISTANCE 5

void sort(char array[][80] , int length)
{
	//sort the artist or songs using simple selection sort
	//I cut down the code from the example given to run a small bit more efficiently and use less variables
	//no need for the "bool" variable minIndexChanged, because we know the minIndex is changed when it is not i anymore
    int minIndex = 0;
    char swap [80];

    for(int i = 0; i < (length-1); i++)
    {
        minIndex = i;
        for(int j = i+1; j < length; j++)
        {
        	//here I used the strcasecmp function instead of strcmp function, because strcasecmp is case sensitive
        	//and lets us avoid the case where for instance "Anvil" would have larger Ascii value than "xylophone"

            if(strcasecmp(array[j], array[minIndex]) < 0)   //if array[j] has a lower ascii value than array[minIndex] change the index
            {
                minIndex = j;
            }
        }

        if(minIndex != i)				//changed guard of if loop
        {
            strcpy(swap, array[i]);		//no need to set the swap string to random characters ending with \0, it already contains strings of 0 terminated with\0
            strcpy(array[i], array[minIndex]);
            strcpy(array[minIndex], swap);
        }
    }
}


void shuffleSongsWithDist(char songs[][MAX_LENGTH], int numOfSongs)
{
    char swap[MAX_LENGTH];								//a string to temporarily hold the random string that is being moved to the front of the playlist
    int inqueue;										//an integer variable used as a boolean variable used for checking if the random index is in the first MIN_DISTANCE strings (queue) at the beggining of the playlist

    time_t t;
    srand((unsigned) time(&t));							//Called to initialise the random number generation

    for(size_t i = 0; i < numOfSongs; i++)				//go through every single string in the sorted playlist from 0 to the numOfSongs
    {
        int j;											//j is our random number index


        //this do while loop keeps on generating random numbers j while the string at j is in the first MIN_DISTANCE songs,
        //the loop is exited and program continues when the string at j is not same as the first MIN_INDEX strings,
        //or a special condition is met to prevent an infinite loop.
        do
        {
            inqueue = 0;								//set inqueue to 0 before every random generation
            j = i + (rand() % (numOfSongs-i));			//generate a random number in range [i , end of the list]

            for (int x = 0; x < MIN_DISTANCE; x++)		//this loop checks if the string at random chosen index is also in the first MIN_DISTANCE positions
            {
                if (strcmp (songs[x], songs[j]) == 0)
                {
                    inqueue = 1;						//if yes, set inqueue to 1 (True) and break out of the iteration of the queue
                    break;
                }
            }

            //1 if an element is in queue at the beginning of the list and
            //2 the ((i - MIN_DISTANCE) >= MIN_DISTANCE) condition checks whether the index has MIN_DISTANCE distance between itself and the end of queue is at least MIN_DISTANCE long ->
            //-> ensuring that paired with the next condition, the shuffling distance will not be disobeyed
            //3 the string at index j can be left at its place only if it is the same index as i ->
            //-> only then we can "skip" the element at index j because we know it is in safe distance from the original value, ensured by the first and second condition
            //-> if j is not equal to i then search the remaining indices for potential new strings to be put to the beginning of the playlist
            if( inqueue && ((i - MIN_DISTANCE) >= MIN_DISTANCE) && (j == i) )
            {
                i++;
            }

            //break out of the loop if the element is not in queue, or
            //if the last element is in the queue and it is left at its place and i is incremented to go out of bounds, therefore break out of the loop
        } while (inqueue || (i==numOfSongs));

        //if we are not at the end of the playlist
        //move all the values from index 1 to index j and put the string at random chosen index j to the index 0 of the playlist
        if (i!= numOfSongs)
        {
            strcpy(swap, songs[j]);
            for (size_t z = j; z > 0; z--)
            {
                strcpy(songs[z], songs[z-1]);
            }
            strcpy(songs[0], swap);
        }
    }
}

void FisherYatesShuffle(char songs[][80], int numOfSongs)
{
    char swap[MAX_LENGTH];						//Initialise a string that will hold a temporary random string

    time_t t;
    srand((unsigned) time(&t));					//Called to initialise the random number generation

    for(size_t i = 1; i < numOfSongs; i++)
    {
        int j = rand() % (i);                   //reduce the initial range, because of the unnecessary iteration at j = i

        strcpy(swap, songs[j]);					//these three lines switch the two strings at index j and i
        strcpy(songs[j], songs[i]);
        strcpy(songs[i], swap);
    }
}

void shuffleSongs(char songs[][MAX_LENGTH], int totalSongs)
{
	//this function decides whether the constrained shuffling is possible to achieve with the number of songs inputed
    if(MIN_DISTANCE >= totalSongs/2)				//if the total of unique songs are less or equal to the MIN_DISTANCE the min_distance in between all songs is not possible to achieve
    {
        printf("\nMinimum distance between songs specified is greater than the number of songs.\nTherefore, here is a shuffled playlist with no restrictions:\n");
        fflush(stdout);
        FisherYatesShuffle(songs, totalSongs);		//therefore, use a shuffle with no constraints
    }
    else
    {
        printf("\nShuffled playlist:\n");
        fflush(stdout);
        shuffleSongsWithDist(songs, totalSongs); 	//if there are more unique songs than the MIN_DISTANCE constraint -> call the shuffling function
    }
}

void printShuffled(char ShuffledSongs[][MAX_LENGTH], int totalSongs)
{
	//a straigth-forward function to print the shuffled songs from array
    for (int x = 0; x < totalSongs; x++)
    {
        printf("%s\n", ShuffledSongs[x]);
        fflush(stdout);
    }
}

