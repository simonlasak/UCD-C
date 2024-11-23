#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sortAndShuffle.h"
#include "helpAndPrint.h"

#define MAX_ARTISTS 4
#define MAX_SONGS 3
#define MAX_LENGTH 80
#define MIN_DISTANCE 5


int song_input(char songs[][MAX_LENGTH], char artist[])
{
	//this function is called by the input function
	//takes care of the input of songs from the terminal and returns the number of songs for each artist

	//the loop is almost identical to the artist input loop but with different prompts and variables
    int numberOfSongs = 0;
    for (; numberOfSongs < MAX_SONGS; numberOfSongs++)
    {
        do
        {
            if(songs[0][1] == '\n')
            {
                printf("Why would you put in no song?\n");
                fflush(stdout);
            }
            printf("Insert song %d for %s\n", numberOfSongs+1,  artist);
            fflush(stdout);
            fgets(songs[numberOfSongs], MAX_LENGTH, stdin);
        } while (songs[0][1] == '\n');

        if(songs[numberOfSongs][1] == '\n')
        {
            break;
        }
        songs[numberOfSongs][strcspn(songs[numberOfSongs], "\n") -1] =0;
    }

    return numberOfSongs;
}

int input(int numOfArtists, char artists[][MAX_LENGTH], int numOfSongs[], char songsOfArtist1[][MAX_LENGTH], char songsOfArtist2[][MAX_LENGTH], char songsOfArtist3[][MAX_LENGTH], char songsOfArtist4[][MAX_LENGTH])
{
	//this function takes care of the input from terminal
	//constraints include:
	//- at least one artist and up to MAX_ARTISTS,
	//- at least one song per artist and up to MAX_SONGS,
	//- if "ENTER" key is pressed the input ends
	//it also calls a function for song_input

    printf("\nEnter at least one artist and at least 1 and at most 3 songs for each artist. \nIf you do not wish to enter more artists or songs press \"Enter\".\n");
    fflush(stdout);
    for (; numOfArtists < MAX_ARTISTS; numOfArtists++)
    {

        do
        {
            if(artists[0][1] == '\n')								//this guard is ignored at first and the prompt 5 lines under is printed
            {														//when the first artist input is the enter key prompt the user to type in at least one artist
                printf("You need to put in at least 1 Artist!");
                fflush(stdout);
            }
            printf("\nInsert an artist/group name:\n" );
            fflush(stdout);
            fgets(artists[numOfArtists], MAX_LENGTH, stdin);		//fgets takes into the string the trailing ENTER character, we take care of that below
        }
        while(artists[0][1] == '\n');								//take in artists from the user while the first character of the first song is the ENTER key
        if(artists[numOfArtists][1] == '\n')						//if the user presses ENTER -> break out of this loop and function
        {
            break;
        }
        printf("\n");
        fflush(stdout);
        //strcspn looks for the trailing newline character and replaces it with the null character, ending the string
        artists[numOfArtists][strcspn(artists[numOfArtists], "\n") - 1] = 0;

        switch (numOfArtists)										//switch statement looking at the current number of artist and calling the song_input with according array of songs
        {
            case 0:
                numOfSongs[0] = song_input(songsOfArtist1, artists[0]);
                break;

            case 1:
                numOfSongs[1] = song_input(songsOfArtist2, artists[1]);
                break;

            case 2:
                numOfSongs[2] = song_input(songsOfArtist3, artists[2]);
                break;

            case 3:
                numOfSongs[3] = song_input(songsOfArtist4, artists[3]);
                break;

            default:
                printf("Error");									//by default, and just in case, there is an Error message displayed and program terminated if anything else other than the expected cases happen
                fflush(stdout);
                return 1;
        }
    }
    return numOfArtists;											//return the number of artists to main
}

int main (void)
{
    char artists[MAX_ARTISTS][MAX_LENGTH];							//initialise all variables and arrays needed
    char sortedArtists[MAX_ARTISTS][MAX_LENGTH];
    char songs1[MAX_SONGS][MAX_LENGTH] = {0};
    char songs2[MAX_SONGS][MAX_LENGTH] = {0};
    char songs3[MAX_SONGS][MAX_LENGTH] = {0};
    char songs4[MAX_SONGS][MAX_LENGTH] = {0};
    char allSongs[MAX_SONGS*MAX_ARTISTS*2][MAX_LENGTH] = {0};

    int numOfArtists = 0;
    int numOfSongs[MAX_ARTISTS] = {0};
    int uniqueSongs = 0;
    int totalSongs;

    //call the function input to take the input from the user whilst saving the returned number of artist into the variable numOfArtists
    numOfArtists = input(numOfArtists, artists, numOfSongs, songs1, songs2, songs3, songs4);

    //copy the array of artists into the array of sorted artists to have both sorted and original artists order
    copyArray(artists, sortedArtists, numOfArtists);

    //sort artists and sort songs of artists
    sort(sortedArtists, numOfArtists);

    sort(songs1, numOfSongs[0]);
    sort(songs2, numOfSongs[1]);
    sort(songs3, numOfSongs[2]);
    sort(songs4, numOfSongs[3]);

    //print the sorted artists and their songs in alphabetical order, this output can be omitted if wanted, so for simple use I used it as a function which can or does not have to be used
    printSongsAndArtists(artists, sortedArtists, songs1, songs2, songs3, songs4, numOfArtists, numOfSongs);

    //use a function to count the number of unique songs input, saving it in a variable we will use later
    uniqueSongs = countSongs(uniqueSongs, numOfSongs);

    //fill the array of all songs with each unique song twice
    fillarray(allSongs, artists, songs1, songs2, songs3, songs4, numOfSongs);
    //now that the array is filled with every song twice the total number of songs is unique songs times two
    totalSongs = uniqueSongs*2;

    //shuffle and print the songs
    shuffleSongs(allSongs, totalSongs);
    printShuffled(allSongs, totalSongs);
}
