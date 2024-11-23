/*
 * helpAndPrint.c
 *
 *  Created on: 23 Feb 2024
 *      Author: imonl
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ARTISTS 4
#define MAX_SONGS 3
#define MAX_LENGTH 80
#define MIN_DISTANCE 5

void copyArray(char artists[][MAX_LENGTH], char sortedArtists[][MAX_LENGTH], int numOfArtists)
{
	//used to copy the original array of the artists into the array of sorted artists,
	//in order to have an array with the original order of artists and then an array of sorted artists,
	//this helps us to match the songs to artists later.

    for(size_t i = 0; i < numOfArtists; i++)
    {
        strcpy(sortedArtists[i], artists[i]);
    }
}

void printSongs(char songs[][MAX_LENGTH], int length)
{
	//function needed to print out songs in a specific format
    for(size_t i = 0; i < length; i++)
    {
        printf("\n%4c %s",'-', songs[i]);
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
}

void printSongsAndArtists(char artists[][MAX_LENGTH], char sortedArtists[][MAX_LENGTH], char songsOfArtist1[][MAX_LENGTH], char songsOfArtist2[][MAX_LENGTH], char songsOfArtist3[][MAX_LENGTH], char songsOfArtist4[][MAX_LENGTH], int lengthArtists, int lengthSongs[])
{
	//function used to match the sorted songs to sorted artists
	//the outer loop is iterating through Sorted artists
    printf("\n\nSorted list of songs:\n");
    fflush(stdout);
    for(size_t i = 0; i < lengthArtists; i++)
    {
        printf("%s", sortedArtists[i]);
        fflush(stdout);
        for(size_t j = 0; j < lengthArtists; j++)
        {
        	//again used strcasecmp just in case
        	//this inner loop is iterating through the artists in the original order
        	//when the original artist at index j is the same as the sorted artist at index i ->
        	//-> the switch function matches the artist to the song depending what the index j is
            if (strcasecmp(sortedArtists[i], artists[j]) == 0)
            {
                switch (j)
                {
                    case 0:
                        printSongs(songsOfArtist1, lengthSongs[0]);
                        break;

                    case 1:
                        printSongs(songsOfArtist2, lengthSongs[1]);
                        break;

                    case 2:
                        printSongs(songsOfArtist3, lengthSongs[2]);
                        break;

                    case 3:
                        printSongs(songsOfArtist4, lengthSongs[3]);
                        break;

                    default:
                        printf("Error");
                        fflush(stdout);
                }
            }
        }
        printf("\n");
        fflush(stdout);

   }
}

int countSongs (int total, int numberOfSongs[])
{
    //add the number of songs for each artists from numberOfSongs[] array to the total
    for (size_t i = 0; numberOfSongs[i] != 0; i++)
    {
        total += numberOfSongs[i];
    }
    return total;
}

int joinArtistsWithSongs(char songs[][MAX_LENGTH], int n, char allSongs[][MAX_LENGTH], int len, char artists[])
{
    //This function formats the strings of songs that are to be printed when shuffled
	//starting at index [n] which keeps incrementing and is returned by this function to the caller function
    for (size_t i = 0; i < len; i++)
    {
        n++;
        strcpy (allSongs[n-1], artists);	//firstly put artist in the allSongs array using strcpy
        strcat(allSongs[n-1], " - ");		//strcat concatenates the right-hand string to the left-hand string (adds it)
        strcat(allSongs[n-1], songs[i]);		//finally again using strcat add the song of the artist to the artists name
    }
    return n;
}

void fillarray (char allSongs[][MAX_LENGTH], char artists[][MAX_LENGTH], char songsOfArtist1[][MAX_LENGTH], char songsOfArtist2[][MAX_LENGTH], char songsOfArtist3[][MAX_LENGTH], char songsOfArtist4[][MAX_LENGTH], int songlength[])
{
    //fill an empty array with the songs of each artist two times
	//it is filled in a way that the first half of array is duplicated into the next half
	//looks like this {A, B, C, D, E, F, A, B, C, D, E, F}

    int n = 0;

    n = joinArtistsWithSongs(songsOfArtist1, n, allSongs, songlength[0], artists[0]);

    n = joinArtistsWithSongs(songsOfArtist2, n, allSongs, songlength[1], artists[1]);

    n = joinArtistsWithSongs(songsOfArtist3, n, allSongs, songlength[2], artists[2]);

    n = joinArtistsWithSongs(songsOfArtist4, n, allSongs, songlength[3], artists[3]);

    n = joinArtistsWithSongs(songsOfArtist1, n, allSongs, songlength[0], artists[0]);

    n = joinArtistsWithSongs(songsOfArtist2, n, allSongs, songlength[1], artists[1]);

    n = joinArtistsWithSongs(songsOfArtist3, n, allSongs, songlength[2], artists[2]);

    n = joinArtistsWithSongs(songsOfArtist4, n, allSongs, songlength[3], artists[3]);
}
