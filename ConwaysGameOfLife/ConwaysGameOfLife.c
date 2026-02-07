// File:            ConwaysGameOfLife.c
// Project:         Conway's Game of Life
// Programmer:      Philip Kempton
// First Version:   2021-05-01
// Description:     This is a solution for Conway's Game of Life (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
//                  This solution focuses on time efficiency for calculating iterations of the game state.

#include <time.h>
#include "Grid.h"

// Prototypes
void getInput(int** gridPtr, int** bufferPtr);

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
    int buffer[GRID_HEIGHT * GRID_WIDTH] = { 0 };
    int* gridPtr = grid;
    int* bufferPtr = buffer;

    // populate grid
    populateGrid(gridPtr);

    // game loop
    while (1)
    {
        // display current grid
        displayGrid(gridPtr);

        // get user input
        getInput(&gridPtr, &bufferPtr);

        // clear screen
        system("cls");
    }

    return 0;
}

// Function:        getInput
// Description:     Gets and acts upon user input.
// Parameters:
//      gridPtr:    Pointer to grid
//      bufferPtr:  Pointer to grid buffer
// Returns:         N/A
void getInput(int** gridPtr, int** bufferPtr)
{
    // display options
    printf("\n1. New Iteration");
    printf("\n2. Reset Grid");
    printf("\n3. Exit");

    // get input repeatedly until a valid option is selected
    char input = 0;
    while (input == 0)
    {
        input = getch();
        switch (input)
        {
        case '1':   // new iteration
            iterateGrid(*gridPtr, *bufferPtr);
            swapPointers(gridPtr, bufferPtr);
            break;
        case '2':   // reset grid
            populateGrid(*gridPtr);
            break;
        case '3':   // exit
            exit(0);
            break;
        default:    // invalid input
            input = 0;
            break;
        }
    }
}
