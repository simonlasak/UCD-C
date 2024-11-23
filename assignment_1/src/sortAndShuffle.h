/*
 * sortAndShuffle.h
 *
 *  Created on: 23 Feb 2024
 *      Author: imonl
 */

#ifndef SORTANDSHUFFLE_H_
#define SORTANDSHUFFLE_H_
#define MAX_LENGTH 80

void sort(char array[][80] , int length);

void shuffleSongsWithDist(char songs[][MAX_LENGTH], int numOfSongs);

void FisherYatesShuffle(char songs[][80], int numOfSongs);

void shuffleSongs(char songs[][MAX_LENGTH], int totalSongs);

void printShuffled(char ShuffledSongs[][MAX_LENGTH], int totalSongs);


#endif /* SORTANDSHUFFLE_H_ */
