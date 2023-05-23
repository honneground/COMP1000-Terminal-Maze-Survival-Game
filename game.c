#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "game.h"

/* Write current position to the linked list record. */
void logPosition(LinkedList* recordList, int* positionList, char actionFront){
    /* Creat the data node*/
    RecordData* newRecord = (RecordData*)malloc(sizeof(RecordData));
    newRecord->playerRow = positionList[0];
    newRecord->playerCol = positionList[1];
    newRecord->monsterRow = positionList[2];
    newRecord->monsterCol = positionList[3];
    newRecord->playerFront = actionFront;
    insertLast(recordList, newRecord);
}


/* Undo function. Receives the the history movement data from the linked list and updates the game map and state accordingly. */
int playerUnMove(int **mapData, int* CrtCoord, LinkedList* recordList, char* Facing){
    /* Player undo result message code.*/
    int mesCode = 0;
    /* Received data type declaration */
    RecordData* undoGuidance;
    if (getSize(recordList) > 0){
        if (getSize(recordList) == CrtCoord[5]){
            CrtCoord[5] = -1;
            CrtCoord[4] = 0;
            mapData[CrtCoord[0]][CrtCoord[1]] = 4;
            mesCode = 1;
        }
        undoGuidance = (RecordData*)removeLast(recordList);
        CrtCoord[0] = undoGuidance->playerRow;
        CrtCoord[1] = undoGuidance->playerCol;
        CrtCoord[2] = undoGuidance->monsterRow;
        CrtCoord[3] = undoGuidance->monsterCol;
        *Facing = undoGuidance->playerFront;
        free(undoGuidance);
        undoGuidance = NULL;
        
    }
    else{
        mesCode = -1;
    }
    return mesCode;
}


/* Receives the user's input from the main function and determines whether the player's movement is valid or not. 
Then updates the game map and state accordingly. */
int playerMove(int **mapData, int rows, int cols, int* CrtCoord, char playerFront, int currentStep){
    /* Store the target coordinates of the player's movement. */
    int tarCol, tarRow;
    /* Player move result message code.*/
    int mesCode=0;
    /* Monster's move direction options. */
    Direction monsterMove = STILL, monsterMoveHor = STILL, monsterMoveVer = STILL;
    /* Initialize the shortest distance to infinity. */
    int leastDistance= INT_MAX;
    /* Monster's distance to the player in four possible direction (ignore the wall) */
    int dis1, dis2, dis3, dis4;
    /* Counts of distances in four directions that match the shortest distance. 
    (It could be 0 to 2, counts 1 is the simplest case, others are a little more tricky) */
    int count = 0;
    /* A flag to optimize the monster's movement. Turn True if player hit the wall. */
    int ahoFlag = 0;

    /* Provide the destination coordinates.*/
    if (playerFront == 'w'){
        tarRow = CrtCoord[0]-1;
        tarCol = CrtCoord[1];
    }else if (playerFront =='s'){
        tarRow = CrtCoord[0]+1;
        tarCol = CrtCoord[1];
    }else if (playerFront =='a'){
        tarRow = CrtCoord[0];
        tarCol = CrtCoord[1]-1;
    }else if (playerFront =='d'){
        tarRow = CrtCoord[0];
        tarCol = CrtCoord[1]+1;
    }

    /* Scenario 1: The destination coordinate is empty. 
    The movement is valid and the player can move to the that location.*/
    if (mapData[tarRow][tarCol] == 0){
        CrtCoord[0] = tarRow;
        CrtCoord[1] = tarCol;
    /* Scenario 2: The destination coordinate contains a key. 
    The movement is valid and the player can move to the that location. 
    The game state will be  updated to indicate that the player has picked up the key.*/
    }else if (mapData[tarRow][tarCol] == 4){
        mapData[tarRow][tarCol] = 0;
        CrtCoord[0] = tarRow;
        CrtCoord[1] = tarCol;
        /*Indicating that player has the key. */
        CrtCoord[4] = 1;
        CrtCoord[5] = currentStep;
        mesCode = 2;
    }
    /* Scenario 3: The destination coordinate is the goal. 
    The movement is invalid. Set a flag to optimize the monster's movement.
    If the player has the key, the movement is valid and the player wins the game. 
    Otherwise, the movement is invalid and the player cannot move to the specified location. */
    else if (mapData[tarRow][tarCol] == 2){
        if (CrtCoord[4] == 1){
            mapData[tarRow][tarCol] = 9;
            CrtCoord[0] = tarRow;
            CrtCoord[1] = tarCol;
            /*Indicating that player won. */
            CrtCoord[4] = -1;
    /* Returns a message code to the main function after a player move, which will then passed to the moveMessenger function to print a status message to the console. */
            mesCode = 3;
        }
        else{
            mesCode = 4;
        }
    }
    /* Scenario 5: The destination coordinate is the wall. 
    The movement is valid only if the player has already picked up the key.
    If the player has the key, the movement is valid and the player wins the game. 
    Otherwise, the movement is invalid and the player cannot move to the specified location. */
    else{ 
        mesCode = 1;
        ahoFlag = 1;
    }

    /* Walk to the monster */
    if (CrtCoord[0] == CrtCoord[2] && CrtCoord[1] == CrtCoord[3]){
        /*Indicating that player suicided. */
        CrtCoord[4] -= 3;
        mesCode += 5;
    /* Monster move (if player wasn't killed yet.) */
        /* Monster can't enter the goal as it don't know the use of the key. */
        /* So player is safe once he/she/they reach the gaol (won). */
        /* But they could step on your key without understand what a key is. */
    }else{
        /* if taget position is valid to move (space or key), count it*/
        leastDistance = abs(CrtCoord[0] - CrtCoord[2]) + abs(CrtCoord[1] - CrtCoord[3]);
        if (mapData[CrtCoord[2]-1][CrtCoord[3]] == 0 || mapData[CrtCoord[2]-1][CrtCoord[3]] == 4){
            dis1 = abs(CrtCoord[0] - (CrtCoord[2]-1)) + abs(CrtCoord[1] - CrtCoord[3]);
            leastDistance = min(dis1 , leastDistance);
            monsterMove = UP;
            monsterMoveVer = UP;
        } else dis1 = -1;
        if (mapData[CrtCoord[2]+1][CrtCoord[3]] == 0 || mapData[CrtCoord[2]+1][CrtCoord[3]] == 4){
            dis2 = abs(CrtCoord[0] - (CrtCoord[2]+1)) + abs(CrtCoord[1] - CrtCoord[3]);
            leastDistance = min(dis2 , leastDistance);
            monsterMove = DOWN;
            monsterMoveVer = DOWN;
        } else dis2 = -1;
        if (mapData[CrtCoord[2]][CrtCoord[3]-1] == 0 || mapData[CrtCoord[2]][CrtCoord[3]-1] == 4){
            dis3 = abs(CrtCoord[0] - CrtCoord[2]) + abs(CrtCoord[1] - (CrtCoord[3]-1));
            leastDistance = min(dis3 , leastDistance);
            monsterMove = LEFT;
            monsterMoveHor = LEFT;
        } else dis3 = -1;
        if (mapData[CrtCoord[2]][CrtCoord[3]+1] == 0 || mapData[CrtCoord[2]][CrtCoord[3]+1] == 4){
            dis4 = abs(CrtCoord[0] - CrtCoord[2]) + abs(CrtCoord[1] - (CrtCoord[3]+1));
            leastDistance = min(dis4 , leastDistance);
            monsterMove = RIGHT;
            monsterMoveHor = RIGHT;
        } else dis4 = -1;
        /* find numbers of shortest valid move */
        if (dis1 == leastDistance) {
            count++;
            monsterMove = UP;
            monsterMoveVer = UP;
        }
        if (dis2 == leastDistance) {
            count++;
            monsterMove = DOWN;
            monsterMoveVer = DOWN;
        }
        if (dis3 == leastDistance) {
            count++;
            monsterMove = LEFT;
            monsterMoveHor = LEFT;
        }
        if (dis4 == leastDistance) {
            count++;
            monsterMove = RIGHT;
            monsterMoveHor = RIGHT;
        }
        /* if more than one shortest valid move found, find the the move that most likely to stop the player from approching its goal (general term of goal, not the exit goal of the maze). */
        if(count>1){
            if(ahoFlag == 1){/* This algorithm can be considered based on the player's previous location which indicates by the player's movement. */
                if(playerFront == 'a' || playerFront == 'd')monsterMove = monsterMoveVer; 
                else monsterMove = monsterMoveHor; 
            }else{
                if(playerFront == 'a' || playerFront == 'd')monsterMove = monsterMoveHor; 
                else monsterMove = monsterMoveVer; 
            }
        }
        /* Conditional compile to enable monster keep still feature. */
        #ifdef KEEPMOVING
        #else
        else if(count == 0){
            monsterMove = STILL;
        }
        #endif
        
        switch(monsterMove) {
        case UP: CrtCoord[2] -= 1; break;
        case DOWN: CrtCoord[2] += 1; break;
        case LEFT: CrtCoord[3] -= 1; break;
        case RIGHT: CrtCoord[3] += 1; break;
        case STILL: break;
        }
        if (CrtCoord[0] == CrtCoord[2] && CrtCoord[1] == CrtCoord[3]){
        /*Indicating that player killed. */
        CrtCoord[4] -= 3;
        mesCode += 10;}
    }
    return mesCode;
}

/* Taking a message code as input and prints the corresponding text message to the console.
The text message provides feedback to the player move. */
void moveMessenger(int mesCode){
    /* The flag indicates whether the player is alive. (and how did they die if they die) */
    int printFlag = 0;/* 0 - alive, 1 - killed, 2 - suicided*/
    if (mesCode>=10){
        mesCode -= 10;
        printFlag = 1;
    }
    if (mesCode>=5){
        mesCode -= 5;
        printFlag = 2;
    }

    if (mesCode == 4) printf("\nYou don't have the key to enter the goal.\n%c", 7);
    else if (mesCode == 3) printf("\nCongratulations on reaching the goal(X).\n You won!\n\n");
    else if (mesCode == 1) printf("\nYou just hit the wall!\n%c", 7);
    else if (mesCode == 2) printf("\nYou got the key!\n");
    if(printFlag == 1) printf("\nThe player was caught by the monster(M) and bitten.\n Game over!\n\n");
    else if(printFlag == 2) printf("\nThe player approached the monster(M) and demised.\n Game over!\n\n");
    else if(mesCode == 0) printf("\n\n\n\n\n");
    else if(mesCode == 1||mesCode == 4) printf("\n\n\n");
}
/* Taking a message code as input and prints the corresponding text message to the console.
The text message provides feedback to the player undo. */
void unmoveMessenger(int mesCode){
    if (mesCode==-1) printf("\nStep count is 0. No movement has been set, and it cannot be undone.\n\n\n\n");
    else if (mesCode==1) printf("\nOps, you lost the key.\n\n\n\n");
    else printf("\n\n\n\n\n");

}

