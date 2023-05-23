#ifndef GAME_H
#define GAME_H
#include "linkedlist.h"
#include "algorithm.h"

/* Entities' history movement data node */
typedef struct {
    int playerRow;
    int playerCol;
    int monsterRow;
    int monsterCol;
    char playerFront;
} RecordData;
/* Monster's move direction data type. */
typedef enum {UP, DOWN, LEFT, RIGHT, STILL} Direction;
void logPosition(LinkedList* recordList, int* positionList, char actionFront);
int playerUnMove(int **mapData, int* CrtCoord, LinkedList* recordList, char* Facing);
int playerMove(int **mapData, int rows, int cols, int* CrtCoord, char playerFront, int currentStep);
void moveMessenger(int mesCode);
void unmoveMessenger(int mesCode);

#endif
