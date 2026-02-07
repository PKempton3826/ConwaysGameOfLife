// File:            ConwaysGameOfLife.c
// Project:         Conways Game of Life
// Programmer:      Philip Kempton
// First Version:   2021-05-01
// Description:     This is a solution for Conways Game of Life (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
//                  This solution focuses on time efficiency for calculating iterations of the game state.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grid.h"

// Input constants
#define ENTER_KEY '\r'
#define BACKSPACE_KEY '\b'
#define ESCAPE_KEY '\x1b'

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
        // display current grid and generate next iteration ahead of time
        displayGrid(gPtr);
        iterateGrid(&gPtr, &bPtr);

        // get user input
        getInput(gPtr);
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
    printf("\nPress ENTER key to tick...");
    printf("\nPress BACKSPACE key to reset...");
    printf("\nPress ESC key to exit...");

    // get input repeatedly until valid option is selected
    char input = 0;
    while (input != ENTER_KEY
        && input != ESCAPE_KEY
        && input != BACKSPACE_KEY)
    {
        input = getch();
    }

    if (input == BACKSPACE_KEY)
    {
        // reset grid
        populateGrid(gPtr);
    }
    else if (input == ESCAPE_KEY)
    {
        // exit application
        exit(0);
    }

    // clear screen
    system("cls");
}
