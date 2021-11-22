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
#include <stdlib.h>
#include <string.h>

struct golfCourse {
    char name[41];
    int holes[18];
    PlayerNode* headNode;
};


Course readCourse(const char * filename){
    Course c;
	FILE* file = fopen(filename,"r");
	if(! file){
	    return NULL;
	}
	char tor[10][100];
	int i;
	int lineNum = 0;
    c = malloc(sizeof(struct golfCourse));
	fgets(tor[lineNum],60,file);
	strcpy(c->name,tor[lineNum]);
	c->name[strlen(c->name)-1] = '\0';
	//printf("%s",c->name);
	lineNum++;
	//printf("%s",c->name);

	fgets(tor[lineNum],36,file);
    int cnt = 0;
	for(i=0;i<36;i++){
	    if((tor[lineNum][i] != ' ') && tor[lineNum][i] != '\0' ){
	        c->holes[cnt] = atoi(&tor[lineNum][i]);
	        //printf("%d ",c->holes[cnt]);
	        cnt++;
	    }
	}
	/*
	Player* play = malloc(sizeof(Player));
	play = newPlayer("empty",c);
    int holeNum;
    lineNum++;
    char pdata[25];
    char* turn;
    char del[2] = ":";
    i = 0;
    int loop = 1;

	while(loop){
	    if(fscanf(file,"%s ",pdata) == EOF){
	        loop = 0;
	    }
	    turn = strtok(pdata,del);
        strcpy(play->name,turn);
        turn = strtok(NULL,del);
        holeNum = atoi(turn);
        turn = strtok(NULL,del);
        strcpy(*play->strokes,turn);
        Player* test = findPlayer(play->name,c);
        if(test == NULL){
            addPlayer(play,c);
            printf("\n %s %s %d",c->headNode->next->player->name,*c->headNode->next->player->strokes,*c->headNode->next->player->strokeScore);
        }
        scoreHole(play,holeNum,*play->strokes);
	}

    */

	fclose(file);


    return c;
}


Player * newPlayer(const char *name, Course course){
    Player* thisPlayer;
    thisPlayer = malloc(sizeof(Player));
    strcpy(thisPlayer->name,name);
    thisPlayer->course = course;
    thisPlayer->parScore[17] = 0;
    thisPlayer->strokeScore[17] = 0;
    for(int i = 0;i<17;i++){
        thisPlayer->strokes[i] = malloc(sizeof(char));
    }
    addPlayer(thisPlayer,course);



    return thisPlayer;
}


int scoreHole(Player* p, int hole, const char* strokes) {
    const char* ptr = strokes;
    p->strokes[hole - 1] = malloc(sizeof(char) * 18);
    p->strokeScore[hole - 1] = strlen(strokes);
    strcpy(p->strokes[hole-1], ptr);
    p->parScore[hole-1] = (p->strokeScore[hole-1]) - (p->course->holes[hole-1]);
    return p->parScore[hole-1];
}
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
    return c->name;
}   // course name
const int * courseHoles(Course c){
    return c->holes;
}   // array of pars for 18 holes
const PlayerNode * coursePlayers(Course c){
    PlayerNode* thisNode;
    thisNode = malloc(sizeof(PlayerNode));
    thisNode = c->headNode;
    return thisNode;
}  // list of all players, alphabetical
PlayerNode * courseLeaders(Course c, int n){
    PlayerNode* thisNode;
    thisNode = malloc(sizeof(PlayerNode));


    return thisNode;
}  // return top n players plus ties
int numPlayers(Course c){
    int num = 0;
    PlayerNode* p = c->headNode;
    while(p){
        num++;
        p = p->next;
    }

    return num;
}  // number of players
/*
Player * findPlayer(const char * name, Course c){
    Player* thisPlayer = malloc(sizeof(Player));
    thisPlayer = NULL;
    //int i;
    PlayerNode* currentPlayer = c->headNode;
    if(c->headNode->next != NULL){ // if there is at least 1 player
        while(currentPlayer != NULL){
            if(strcmp(currentPlayer->next->player->name, name) == 0){
                thisPlayer = currentPlayer->next->player;

            }
                currentPlayer = currentPlayer->next;
            }
        }

    return thisPlayer;
}  // find and return a specific player

*/
Player* findPlayer(const char * name, Course c) {
    Course thisCourse = c;
    char checkName[10];
    strcpy(checkName, name);
    Player* returnValue = NULL;
    PlayerNode* currentNode = thisCourse->headNode;
    if (numPlayers(thisCourse) >= 0) {
        if ((strcmp(currentNode->player->name, checkName)) == 0)
        {
            returnValue = thisCourse->headNode->player;
        }

        while (currentNode != NULL) {
            if (strcmp(currentNode->player->name, checkName) == 0) {
                returnValue = currentNode->player;
                break;
            }
            else {
                currentNode = currentNode->next;
            }
        }
    }
    return returnValue;
}


void addPlayer(Player* p, Course c) {
    Course thisCourse = c;
    PlayerNode* newPlayer = NULL;
    PlayerNode temp;
    temp.next = thisCourse->headNode;
    newPlayer = (PlayerNode*)malloc(sizeof(PlayerNode));
    newPlayer->player = p;
    newPlayer->next = NULL;
    int alpha = 0;
    if (thisCourse->headNode == NULL) {
        thisCourse->headNode = newPlayer;
    }
    else {
        PlayerNode* currentnode = thisCourse->headNode;
        PlayerNode* prevNode = &temp;
        while(currentnode != NULL){
            alpha = strcmp((currentnode->player->name), (newPlayer->player->name));
            if ((alpha > 0))
            {
                prevNode->next = newPlayer;
                newPlayer->next = currentnode;
                thisCourse->headNode = temp.next;
                return;
            }
            else if (alpha == 0) {break;}
            prevNode = currentnode;
            currentnode = currentnode->next;
        }
        prevNode->next = newPlayer;
    }
}
double avgTotalScore(Course c){
    return 0;
}   // return average stroke score for all players in list
double avgParScore(Course c){
    return 0;
}     // return average par score for all players in list
double avgHoleScore(Course c, int hole){
    return 0;
}    // return average stroke score for a particular hole


