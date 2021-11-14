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

struct Course {
    char name[16];
    char holes[18];
    PlayerNode* headNode;

    //players as a liked list (wtf)

};


Course readCourse(const char * filename){
	FILE* file = fopen(filename,"r");
	if(! file){
	    return NULL;
	}
	char tor[10][150];
	int i;
	for(i=0;i<10;i++){
	    fgets(tor[i],150,file);
	    printf("%s",tor[i]);
	}
	fclose(file);
	Course read;

    return read;
}

int scoreHole(Player *p, int hole, const char* strokes){
    return 0;
}  // hole is between 1 and 18
int totalStrokeScore(const Player *p){
    return 0;
}  // total number of strokes on all holes played
int totalParScore(const Player *p){
    return 0;
}     // total score relative to par (e.g., 2 means two-over-par) on all holes played
int greensInReg(const Player *p){
    return 0;
}       // number of greens reached in (par - 2) strokes, for all holes played
void fairwaysHit(const Player *p, int *hit, int *holes){

}    // fairways hit (only for par-4 and par-5 holes), for all holes played
int countScores(const Player *p, int parScore){
    return 0;
} // returns number of times player achieved a certain par-score on any hole
// for example, caller would set parScore to -1 to count the number of birdies on holes played so far


 // read course and score info from file
const char * courseName(Course c){
    return NULL;
}   // course name
const int * courseHoles(Course c){
    return 0;
}   // array of pars for 18 holes
const PlayerNode * coursePlayers(Course c){
    PlayerNode* thisNode;

    return thisNode;
}  // list of all players, alphabetical
PlayerNode * courseLeaders(Course c, int n){
    PlayerNode* thisNode;
    return thisNode;
}  // return top n players plus ties
int numPlayers(Course c){
    return 0;
}  // number of players
Player * findPlayer(const char * name, Course c){
    Player* thisPlayer;
    return thisPlayer;
}  // find and return a specific player
void addPlayer(Player *p, Course c){

}  // add a player to course list

double avgTotalScore(Course c){
    return 0;
}   // return average stroke score for all players in list
double avgParScore(Course c){
    return 0;
}     // return average par score for all players in list
double avgHoleScore(Course c, int hole){
    return 0;
}    // return average stroke score for a particular hole


