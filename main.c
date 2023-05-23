#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "map.h"
#include "game.h"
#include "terminal.h"
#include "linkedlist.h"

/* welcome page */
void welcome(){
    printf("\n_____________________________________________________________________________________\n\n");
    printf("███╗   ███╗ █████╗ ███████╗███████╗     ██████╗ █████╗  ███╗   ███╗███████╗    ██╗██╗\n");
    printf("████╗ ████║██╔══██╗╚══███╔╝██╔════╝    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██║██║\n");
    printf("██╔████╔██║███████║  ███╔╝ █████╗      ██║  ███╗███████║██╔████╔██║█████╗      ██║██║\n");
    printf("██║╚██╔╝██║██╔══██║ ███╔╝  ██╔══╝      ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║██║\n");
    printf("██║ ╚═╝ ██║██║  ██║███████╗███████╗    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ██║██║\n");
    printf("╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚═╝╚═╝");
    printf("\n_____________________________________________________________________________________");
}

/* The "main" function which initializes the game and passes data between various components of the program. */
int main(int argc, char** argv) {
    /* An integer variable to store the total number of rows in the world data array. aka. numbers of element in the map.*/
    int worldDataAmount;
    /* An integer variable to store the number of rows in the maze map */
    int worldRow;
     /* An integer variable to store the number of cols in the maze map */
    int worldCol;
    /* A pointer to a pointer of integers to store the address of the dynamically allocated 2D array that will hold the locations of elements in the map.*/
    int** worldData;
    /* A pointer to a pointer of integers to store the address of the dynamically allocated 2D array that will hold the world data.*/
    int** mapData;
    /* Two integer variable to serve as loop counter variables in the subsequent code.*/
    int i, j;
    /* Maximum distance at which an element can be seen by the player. 
    By default, it is initialised to a value of 0 and can be overwritten with another value if needed.*/    
    int visibilityDistance = 0;
    /*  Store the input from the user to move the player which expected to be in the form of the keys "w", "a", "s", and "d" as directional keys in games.*/
    char charIn;
    /* An integer array to indicate the entitis's position[entitisStateArr[0/2] for rows, entitisStateArr[1/3] for cols] and game status.
    0 and 1 for player, 2 and 3 for the monster.

    entitisStateArr[4] is being used to store the game status. Specifically:
    0 indicates that the player does not have the key and the game is still in progress.
    1 indicates that the player has the key.
    -1 indicates that the player has won the game and the game is over.
    -2 indicates that the player has lost the game and the game is over.

    entitisStateArr[5] is the round/step the player got the key.*/
    int entitisStateArr[6]={0,0,0,0,0,-1};/*[5] = -1 indicate the key is not got in any step */
    /* The warningFlag variable is used to prevent duplicate warning messages from being printed to the terminal.
    If a warning message has already been printed and not cleared, a beep will also be played to alert the user instead.*/
    int warningFlag = 1;
    /* Player move result message code.*/
    int mesCode;
    /* These variables are intermediate variables used to fill the mapData from the worldData in the for loop."*/
    int objCode, row, col;
    FILE *mapFile;
    /* Debug mode flag*/

    /* store player's movement in last step. (a.k.a the direction player facing now) */
    char lastmove;
    /* History position log stored for undo */
    LinkedList* positionRecord;

    /* Read the data file name from the command line argument */
    if (argc != 2) {
        welcome();
        printf("\n\nUsage: %s <map_file_name>\n\n", argv[0]);
        return 1;
    }

    mapFile = fopen(argv[1], "r");
    if (mapFile == NULL) {
        welcome();
        printf("\n\nError opening file: %s\n\n", argv[1]);
        return 1;
    }
    
    /* The following code is only included if the DARK macro is defined.*/
    /* In the case DARK in defined, we use the DARK macro to enable a visibility feature by overwriting the visibilityDistance with the argv integer.*/ 
    /* This code calls the "disableBuffer" function from "terminal.c" to enable continuous input without requiring the user to press "Enter". */
    disableBuffer();

    /* Plash Page */
    /* This section of code displays the welcome page, which provides instructions of the program.*/

    system("clear");
    welcome();
    printf("\n\nWelcome to the Maze Game!\n\n");
    printf("Your objective is to find the key (k) and then reach the goal (x),\n");
    printf(" while avoiding caught by the monster(m).\n");
    printf("Use WASD keys to move around the maze, and U to undo.\n");
    printf("Press Q to quit the game at any time.\n\n");
    printf("Please ensure that CapsLock is turned off.\n");
    printf("\nPress any key to continue...");
    getchar();
    system("clear");

    /* Map Initialization (Although it may appear lengthy due to the comments, there is actually not a significant amount of codes.)*/

    /* Our map initialization code is relatively simple and # ONLY USED IN ONE PLASE #. I choose the approach that avoids introducing additional files and complexity. 
    If the map initialization code is not placed in the main, and instead is redundantly defined and called wordData and mapData in multiple files, 
    it would lead to code redundancy and increased memory usage, which can affect the performance and stability of the application. 
    Therefore, it's not a great approach in this scenario to place the map initialization code in a separate function or file. 
    Remaining initialization in the main function can help avoid redundant calls and improve code reusability and maintainability. */
    
    /* Passing the file pointer and request the fundamental information and distribution of elements on the map.*/
    worldData = getWorldData(mapFile, &worldDataAmount, &worldRow, &worldCol);/* File pointer would be closed in the getWorldData after it's usage. */

    /* Create a dynamically allocated 2D array ready to be filled up with map data, using calloc() to avoid the need for initialization.*/
    mapData = (int**)calloc(worldRow, sizeof(int*)); 
    for (i = 0; i < worldRow; i++) {
        mapData[i] = (int*)calloc(worldCol, sizeof(int));
    }

    /* Populate the map data according to worldData.*/
    for (i = 0; i < worldDataAmount; i++) {
        row = worldData[i][0] ; 
        col = worldData[i][1] ; 
        objCode = worldData[i][2];
        if (objCode == 0){
            /* Record the player's position */
            entitisStateArr[0] = row; 
            entitisStateArr[1] = col;
        }
        else if (objCode == 1){
            /* Record the player's position */
            entitisStateArr[2] = row; 
            entitisStateArr[3] = col;
        }
        else mapData[row][col] = objCode;
        
    }

    /*After adding elements to the map, free the memory used for the table of the location of each element.*/
    for(i = 0; i < worldDataAmount; i++) {/* Free the memory for each array pointed to by the pointers */
        free(worldData[i]);
        worldData[i] = NULL;
    }
    free(worldData);/* Free the memory and the pointer allocate to the temp array. */
    worldData = NULL;

    /* Setting up borders by filling the first and last columns and rows with the object code for the wall*/
    for (j = 0; j < worldCol; j++) {/* set the top and bottom rows to 2*/
        mapData[0][j] = 3; /* top row */
        mapData[worldRow - 1][j] = 3; /* bottom row */
    }
    for (i = 0; i < worldRow; i++) {/* set the left and right columns to 2 */
        mapData[i][0] = 3; /* left column */
        mapData[i][worldCol - 1] = 3; /* right column */
    }

    positionRecord = createLinkedList();/* Initiate the history movement data log */
    /* Prints the initial state of the game map. */
    printMap(mapData, worldRow, worldCol, entitisStateArr, visibilityDistance, 'w', getSize(positionRecord));
    lastmove = 'w';
    moveMessenger(0);
    
    /* Checks whether the game is over by checking if the user has pressed 'q' to quit or has won the game. 
    If either condition is true, the while loop is terminated, and the game is ended. */
    while (charIn !='q'&& entitisStateArr[4]>=0){
        /* Scenario 1: If the user inputs 'q', the game loop will then be ended.*/
        charIn = getchar();
        if (charIn == 'q'){
            system("clear");
            printMap(mapData, worldRow, worldCol, entitisStateArr, visibilityDistance, charIn, getSize(positionRecord));
            printf("\nThe game has been exited. Thank you for playing!\n");
        }
        /*Scenario 2: If the user inputs a valid character ('w', 'a', 's', 'd'), 
        the character will be passed as an argument to the playerMove() function, which updates the game state based on the player's movement.*/

        else if(charIn == 'a' || charIn == 's' || charIn == 'd' || charIn == 'w'){

            warningFlag = 1;
            logPosition(positionRecord, entitisStateArr, lastmove);
            mesCode = playerMove(mapData, worldRow, worldCol, entitisStateArr, charIn, getSize(positionRecord));
            system("clear");/* Clean the terminal for Linux system.*/
            printMap(mapData, worldRow, worldCol, entitisStateArr, visibilityDistance, charIn, getSize(positionRecord));
            moveMessenger(mesCode);
            lastmove = charIn;
        }
        /*Scenario 3: If the user inputs an valid character 'u' for undo.*/ 
        else if(charIn == 'u'){
            warningFlag = 1;
            mesCode = playerUnMove(mapData, entitisStateArr, positionRecord, &charIn);
            system("clear");
            printMap(mapData, worldRow, worldCol, entitisStateArr, visibilityDistance, charIn, getSize(positionRecord));
            unmoveMessenger(mesCode);
        /*Scenario 4: If the user inputs an invalid character.The user will then be prompted to try again.*/ 
        }
        else if(warningFlag == 1){
            printf("\n#Warning: Invalid input!#\n%c",7);
            printf("Use WASD keys to move around.\n");
            printf("Press Q to quit the game\n\n");
            printf("Ensure that CapsLock is turned off.\n");
            
        /* The warningFlag variable is used to prevent duplicate warning messages from being printed to the terminal.
        If a warning message has already been printed and not cleared, a beep will also be played to alert the user instead.*/
            warningFlag = 0;
        }
        else printf("%c",7);/*Beep*/
    }
    /*After adding maze is end, free the memory used for the maze.*/
    for(i = 0; i < worldRow; i++) {/* Free the memory for each array pointed to by the pointers */
        free(mapData[i]);
        mapData[i] = NULL;
    }
    free(mapData);/* Free the memory and the pointer allocate to the map data array */
    mapData = NULL;
    
    /* Free the memory and the pointer (freeList()'s duty) AND datas allocate to the array (clearData()'s duty) of the history movement log linked list */
    clearData(positionRecord);
    freeList(positionRecord);
    enableBuffer();
    
    if(charIn != 'q'){
        printf("Press \"Enter\" to exit the game... ");
        getchar();  
    }
       
    return 0;
}
