#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"

/* print the mapData array with border*/
void printMap(int **mapData, int rows, int cols, int* CrtCoord, int viewRange, char playerFace, int stepCount){
    /* Two integer variable to serve as loop counter variables in the subsequent code.*/
    int i, j;

    /* prints the top border of the map based on the number of columns. 
    By avoiding direct access to the map data, it improves runtime efficiency and reduces memory usage.*/

    /* Declare valuables to calculate the visible range of the player.*/
    int rowStart;
    int rowEnd;
    int colStart;
    int colEnd;
    int monsterSteponFlag = 0;
    

    /* Perform the calculation only when it is necessary (viewRange != 0) to save memory and improve performance. */
    if (viewRange != 0){
        rowStart = max(0, CrtCoord[0] - viewRange);
        rowEnd = min(rows-1, CrtCoord[0] + viewRange);
        colStart = max(0, CrtCoord[1] - viewRange);
        colEnd = min(cols-1, CrtCoord[1] + viewRange);
    }

    /* Traverse the map.*/
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            /* Check if the position is outside of the visible range */
            if((viewRange != 0)&&(i < rowStart || i > rowEnd || j < colStart || j > colEnd)){
                    printf(" "); /* Print whitespace if outside visible range.*/
            }else{
                /* Check if the position needs to be displayed.*/
                if (mapData[i][j] != 0) {
                    /* Print the corresponding character based on the value.*/
                    if((i == 0 || i == rows-1)&&(j == 0 || j == cols-1)){
                        printf("#");
                    } else if(i == 0 || i == rows-1){
                        printf("-");
                    } else if(j == 0 || j == cols-1){
                        printf("|");
                    } else if(mapData[i][j] == 2){
                        if(i == CrtCoord[2] && j == CrtCoord[3]){
                            monsterSteponFlag = 2;
                            printf("M");
                        }
                        else printf("x");
                    } else if (mapData[i][j] == 3){
                        printf("o");
                    } else if (mapData[i][j] == 4){
                        if(i == CrtCoord[2] && j == CrtCoord[3]){
                            monsterSteponFlag = 1;
                            printf("M");
                        }
                        else printf("k");
                    } else if (mapData[i][j] == 9){
                        printf("X");
                    } else {
                        printf(" "); /* Print whitespace if unknown value.*/
                    }
                } else {
                        if (i == CrtCoord[2] && j == CrtCoord[3]){
                            if(CrtCoord[4] >-2)printf("m");
                            else printf("M");
                        } 
                        else if (i == CrtCoord[0] && j == CrtCoord[1]){
                            if(playerFace == 's')printf("v");
                            else if (playerFace == 'd')printf(">");
                            else if (playerFace == 'a')printf("<");
                            else printf("^");
                        }else printf(" "); /* Print whitespace if value is zero.*/

                }
            }
        }
        printf("\n"); /* Print newline after each row.*/
    }
    if(CrtCoord[4]==0||CrtCoord[4]==-3) printf("\nToolbar: [Empty]\t");
    else printf("\nToolbar: [Key]\t");
    printf("Step: %d\n", stepCount);
    if(monsterSteponFlag == 1)printf("Oops! The monster(M) has stepped on the key. Redirect its attention away from it.");
    if(monsterSteponFlag == 2)printf("Uh-oh! The monster(M) is guarding the goal. Redirect its focus away from the goal.");
    /* For debugging purposes only. 
    It prints out the original data array for the map, which can be useful in identifying any errors in the initialization or manipulation of the map data.*/
}
