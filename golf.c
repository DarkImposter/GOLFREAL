// ECE 209 - Fall 2021 - Program 3
// This program reads information about a golf tournament
// and allows a user to view information about the course,
// the overall scores, and the individual players.
//
// Implementation of Course ADT and functions for Player and PlayerNode types
//
// Parker Sexton
//whats up

#include "golf.h"
#include <stdio.h>




Course readCourse(){
	FILE* file = fopen("TorreyPines.txt","r");
	char tor[10][150];
	int i;
	for(i=0;i<10;i++){
	    fgets(tor[i],150,file);
	    printf("%s",tor[i]);
	}
	fclose(file);

}



