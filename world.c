#include <stdlib.h>
#include <stdio.h>
#include "world.h"

/* Read from the file pointer and fill the data into the table */
int** getWorldData(FILE* mapFile, int * worldDataAmount, int * worldRow, int * worldCol)
{
    /* The integer variable to serve as loop counter variables in the subsequent code.*/
    int i;
    /* Table of world data to return. */
    int ** table;

    /* Read the first row */
    fscanf(mapFile, "%d", worldDataAmount); /* amount of the objects in the playable area */
    fscanf(mapFile, "%d", worldRow);        /* The world row size I will create later */
    fscanf(mapFile, "%d", worldCol);        /* The world column size I will create later */

    /* Init the table based on the data from the first line*/
    table = (int**)malloc(sizeof(int*) * (*worldDataAmount));

    /* Read the following row */
    for (i = 0; i < (*worldDataAmount); i++) {
        table[i] = (int*)malloc(sizeof(int) * 3);
        fscanf(mapFile, "%d %d %d", &table[i][0], &table[i][1], &table[i][2]);
    }

    fclose(mapFile);

    return table;/* return the array */
}

