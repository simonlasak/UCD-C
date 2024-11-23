/*
 * helpAndPrint.h
 *
 *  Created on: 23 Feb 2024
 *      Author: imonl
 */

#ifndef HELPANDPRINT_H_
#define HELPANDPRINT_H_
#define MAX_LENGTH 80

void copyArray(char artists[][MAX_LENGTH], char sortedArtists[][MAX_LENGTH], int numOfArtists);

void printSongs(char songs[][MAX_LENGTH], int length);

void printSongsAndArtists(char artists[][MAX_LENGTH], char sortedArtists[][MAX_LENGTH], char songsOfArtist1[][MAX_LENGTH], char songsOfArtist2[][MAX_LENGTH], char songsOfArtist3[][MAX_LENGTH], char songsOfArtist4[][MAX_LENGTH], int lengthArtists, int lengthSongs[]);

int countSongs (int total, int numberOfSongs[]);

int joinArtistsWithSongs(char songs[][MAX_LENGTH], int n, char allSongs[][MAX_LENGTH], int len, char artists[]);

void fillarray (char allSongs[][MAX_LENGTH], char artists[][MAX_LENGTH], char songsOfArtist1[][MAX_LENGTH], char songsOfArtist2[][MAX_LENGTH], char songsOfArtist3[][MAX_LENGTH], char songsOfArtist4[][MAX_LENGTH], int songlength[]);


#endif /* HELPANDPRINT_H_ */
