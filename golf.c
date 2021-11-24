// ECE 209 - Fall 2021 - Program 3
// This program reads information about a golf tournament
// and allows a user to view information about the course,
// the overall scores, and the individual players.
//
// Implementation of Course ADT and functions for Player and PlayerNode types
//
// Parker Sexton
// 11/24/21

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


Course readCourse(const char* filename) {
    FILE* file = fopen(filename, "r");
    Course c;
    char tor[15][150];
    int count = 0;
    int lineNum = 0;
    c = malloc(sizeof(struct golfCourse));//For each line

    fgets(tor[lineNum], 100, file); //Get the name of the course
    strcpy(c->name, tor[0]);
    c->name[strlen(c->name)-1] = '\0';
    lineNum++;
    fgets(tor[lineNum], 100, file); //Get the name of the course

    count = 0;
    for (int i = 0; i < (18 * 2); i++) {
        if ((tor[1][i] != ' ') && (tor[1][i] != '\0')) {
            c->holes[count] = atoi(&tor[1][i]);	//Parse the list of characters in the
            count++;												//strings of pars to list of ints
        }
    }
    char turnInfo[25];
    char lastTurn[25];
    int doLoop = 1;
    while (doLoop) {
        if(fscanf(file, "%s ", turnInfo) == EOF){
            return c;
        }
        if (strcmp(lastTurn, turnInfo) != 0) {
            char* turnData;
            turnData = malloc(20 * sizeof(char));
            int holeNumber;
            char delim[2] = ":";
            turnData = strtok(turnInfo, delim);
            Player* playerExists = findPlayer(turnData, c);
            if (playerExists == NULL) {
                addPlayer(newPlayer(turnData, c), c);
                playerExists = findPlayer(turnData, c);
            }
            turnData = strtok(NULL, delim);
            holeNumber = atoi(turnData);
            turnData = strtok(NULL," ");
            scoreHole(playerExists, holeNumber, turnData);
            strcpy(lastTurn, turnInfo);

        }
        else {
            doLoop = 0;
        }
    }

    fclose(file);
    return c;
}

Player * newPlayer(const char *name, Course course){
    Player* this = malloc(sizeof(Player));
    strcpy(this->name,name);//store
    this->course = course;
    this->parScore[17] = 0;
    this->strokeScore[17] = 0;
    for(int i = 0;i<17;i++){
        this->strokes[i] = malloc(sizeof(char));
        this->strokes[i] = 0;
    }
    addPlayer(this,course);
    return this;
}


int scoreHole(Player* p, int hole, const char* strokes) {
    if(strokes == NULL){
        return 0;
    }
    const char* ptr = strokes;
    p->strokes[hole - 1] = malloc(sizeof(char)*18);
    p->strokeScore[hole - 1] = strlen(strokes);
    strcpy(p->strokes[hole-1], ptr);
    p->parScore[hole-1] = (p->strokeScore[hole-1]) - (p->course->holes[hole-1]);
    return p->parScore[hole-1];
}
int totalStrokeScore(const Player *p){
    int score = 0;
    int i;
    if(findPlayer(p->name,p->course)){
        for(i=0;i<18;i++){
            score += p->strokeScore[i];
        }
    }
    return score;
}  // total number of strokes on all holes played
int totalParScore(const Player *p){
    int score = 0;
    int i;

    for(i=0;i<18;i++){
        if(p->strokeScore[i] == 0){
            return score;
        }
        score += (p->strokeScore[i]) - (p->course->holes[i]);

    }

    return score;
}     // total score relative to par (e.g., 2 means two-over-par) on all holes played
int greensInReg(const Player *p){
    int greens = 0;
    int i;
    int l;
    for(i=0;i<18;i++){
        for(l=0;l< p->course->holes[i] -2; l++){
            if(p->strokes[i][l] == 'g' || p->strokes[i][l] == 'h'){
                greens++;
            }
        }
    }
    return greens-1;
}       // number of greens reached in (par - 2) strokes, for all holes played
void fairwaysHit(const Player *p, int *hit, int *holes){
    int i;
    for(i=0;i<18;i++){
        if(p->course->holes[i] > 3){
            (*holes)++;
            if(p->strokes[i][0] == 'f'){
                (*hit)++;
            }
        }

    }
}    // fairways hit (only for par-4 and par-5 holes), for all holes played
int countScores(const Player *p, int parScore){
    int score = 0;
    int i;
    for(i=0;i<18;i++){
        if(p->parScore[i] == parScore){
            score++;
        }
    }
    return score;
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
    //int num = numPlayers(c);

    return thisNode;
}  // list of all players, alphabetical
PlayerNode * courseLeaders(Course c, int n){
    PlayerNode* thisNode;
    thisNode = malloc(sizeof(PlayerNode));


    return thisNode;
}  // return top n players plus ties


int numPlayers(Course c) {
    PlayerNode* thisNode = malloc(sizeof(struct golfPlayerNode));
    thisNode->next = c->headNode;//Point to head
    thisNode->player = NULL;
    int playerCount = 0;
    if(thisNode->next == NULL){
        return 0;
    }

    {
        while (thisNode != NULL) {//run while loop
            thisNode = thisNode->next;
            playerCount++;
        }
    }


    return playerCount-1;
}

Player* findPlayer(const char * name, Course c) {
    Player* returnValue = malloc(sizeof(Player));
    returnValue = NULL;
    if(c->headNode == NULL){
        return returnValue;
    }
    PlayerNode* currentNode = malloc(sizeof(PlayerNode));
    currentNode = c->headNode;
    if (numPlayers(c) >= 0) { // if one player exists
        if ((strcmp(currentNode->player->name, name)) == 0){
            returnValue = c->headNode->player; //return that player if name match
            return returnValue;
        }

        while (currentNode != NULL) {
            if (strcmp(currentNode->player->name, name) == 0) {
                returnValue = currentNode->player;
                return returnValue;
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
    PlayerNode* temp = malloc(sizeof(PlayerNode));
    temp->next = thisCourse->headNode;
    newPlayer = malloc(sizeof(PlayerNode));
    newPlayer->player = p;
    newPlayer->next = NULL;
    if (thisCourse->headNode == NULL) {
        thisCourse->headNode = newPlayer;
    }
    else {
        PlayerNode* currentnode = thisCourse->headNode;
        PlayerNode* prevNode = temp;
        while(currentnode != NULL){
            if ((strcmp((currentnode->player->name), (newPlayer->player->name)) > 0))
            {
                prevNode->next = newPlayer;
                newPlayer->next = currentnode;
                thisCourse->headNode = temp->next;
                return;
            }
            else {
                if(strcmp((currentnode->player->name), (newPlayer->player->name)) == 0){
                    return;
                }
            }
            prevNode = currentnode;
            currentnode = currentnode->next;

        }
        prevNode->next = newPlayer;
    }
}
double avgTotalScore(Course c){
    double avg = 0;
    int players = numPlayers(c);
    PlayerNode* p = malloc(sizeof(PlayerNode));
    p = c->headNode;
    if(c->headNode->next){
        while(p->next){
            avg += totalStrokeScore(p->player);
            p = p->next;
        }
    }
    avg += totalStrokeScore(p->player);
    avg /= players;
    return avg;
}   // return average stroke score for all players in list
double avgParScore(Course c){
    PlayerNode* p = malloc(sizeof(PlayerNode));
    double avg = 0;
    int players = numPlayers(c);
    p = c->headNode;
    if(c->headNode->next){
        while(p->next){
            avg += totalParScore(p->player);
            p = p->next;
        }
    }
    avg += totalParScore(p->player);
    avg /= players;
    return avg;
}     // return average par score for all players in list
double avgHoleScore(Course c, int hole){
    PlayerNode* p = malloc(sizeof(PlayerNode));
    double avg = 0;
    int players = numPlayers(c);
    p = c->headNode;
    if(c->headNode->next){
        while(p->next){
            avg += p->player->strokeScore[hole-1];
            p = p->next;
        }
    }
    avg += p->player->strokeScore[hole-1];
    avg /= players;
    return avg;
    return 0;
}    // return average stroke score for a particular hole

