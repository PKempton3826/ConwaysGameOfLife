// File:            ConwaysGameOfLife.c
// Project:         Conways Game of Life
// Programmer:      Philip Kempton
// First Version:   2021-05-01
// Description:     This is a solution for Conway's Game of Life (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
//                  This solution focuses on time efficiency for calculating iterations of the game state.

#include <time.h>
#include "Grid.h"

// Prototypes
void getInput(int* gPtr);


// Function:    main
// Description: Main entry point for application.
// Parameters:  N/A
// Returns:     0
int main()
{
    // seed rand
    srand(time(0));

    // define grids and pointers
    int grid[GRID_HEIGHT * GRID_WIDTH] = { 0 };
    int buff[GRID_HEIGHT * GRID_WIDTH] = { 0 };
    int *gPtr = grid;
    int *bPtr = buff;

    // populate grid
    populateGrid(gPtr);

    // game loop
    while (1)
    {
        // display current grid
        displayGrid(gPtr);

        // generate new iteration ahead of time
        iterateGrid(&gPtr, &bPtr);

        // get user input
        getInput(gPtr);

        // clear screen
        system("cls");
    }

    return 0;
}

// Function:    getInput
// Description: Gets and acts upon user input.
// Parameters:
//      gPtr:   Pointer grid
// Returns:     N/A
void getInput(int* gPtr)
{
    // display options
    printf("\n1. New Iteration");
    printf("\n2. Reset Grid");
    printf("\n3. Exit");

    // get input repeatedly until a valid option is selected
    char input = 0;
    while (input != '1'
        && input != '2'
        && input != '3')
    {
        input = getch();
    }

    if (input == '2')
    {
        // reset grid
        populateGrid(gPtr);
    }
    else if (input == '3')
    {
        // exit application
        exit(0);
    }
}
