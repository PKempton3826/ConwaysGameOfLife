// File:    ConwaysGameOfLife.c
// Project: Conways Game of Life
// Programmer:  Philip Kempton
// First Version:   2021-05-01
// Description: This is a solution for Conways Game of Life (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
//              This solution focuses on time efficiency for calculating iterations of the game state.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_HEIGHT 20
#define GRID_WIDTH 20

// Function:    displayGrid
// Description: Displays a grid of ones and zeros as '0's and '-'s, respectively.
//              Displays 'x' for invalid cell data (bad input).
// Parameters: 
//      grid:   The grid to display
// Returns:     No return
void displayGrid(int *grid)
{
    // formatted string for displaying a char with enough padding to take up 2 digits
    const char formattedCellStr[] = "%2c";
    for (int row = 0; row < GRID_HEIGHT; row++)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            if (grid[(row * GRID_WIDTH) + col] == 1)
            {
                printf(formattedCellStr, '0');
            }
            else if (grid[(row * GRID_WIDTH) + col] == 0)
            {
                printf(formattedCellStr, '-');
            }
            else
            {
                // bad input, display 'x' to signify an invalid cell
                // this should not happen
                printf(formattedCellStr, 'x');
            }
        }
        printf("\n");
    }
}

// Function:    populateGrid
// Description: Randomly populates a grid with 1's and 0's.
//              Attempts a random 50% split but relies on rand() so even distribution is not guaranteed.
// Parameters: 
//      grid:   The grid to populate
// Returns:     No return
void populateGrid(int *grid)
{
    // For each cell, get a random integer and assign the cell as 1 if it's even, otherwise assign it as 0
    int *end = grid + (GRID_HEIGHT * GRID_WIDTH);
    for (int *cell = grid; cell != end; ++cell)
    {
         if ( (rand() % 2) == 0)
         {
             *cell = 1;
         }
         else
         {
             *cell = 0;
         }
    }
    *grid = 1;
}

// Function:        tickGrid (TODO: fix function name)
// Description:     Ticks the grid (TODO: fix comment)
// Parameters:
//      gridIn:     The input grid for calculating the next iteration
//      gridOut:    The output grid for returning the newly calculated iteration
// Returns:         No return
void tickGrid(int *gridIn, int *gridOut)
{
    // TODO: Commenting for this, needs explaining 
    // (explain efficiency of using a lookup-array as apposed to conditionals)
    int *inCell = gridIn;
    int *outCell = gridOut;
    int resultArray[] = { 
        0, 0, 0, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, // No-Man's-Land, unused indeces
        0, 0, 1, 1, 0, 0, 0, 0, 0 
    };

    int *BN = inCell + GRID_WIDTH;
    int *RN = inCell + 1;
    int *BRN = inCell + GRID_WIDTH + 1;

    // first row
    // first char
    *outCell = resultArray[(*BN + *BRN + *RN) | (*inCell << 4)];

    // middle cols
    int* end = inCell + GRID_WIDTH - 1;
    inCell++; outCell++; BN++; BRN++; RN++;
    int* LN = inCell - 1;
    int* BLN = inCell + GRID_WIDTH - 1;
    for (; inCell < end; ++inCell, ++outCell, ++LN, ++BLN, ++BN, ++BRN, ++RN)
    {
        *outCell = resultArray[(*LN + *BLN + *BN + *BRN + *RN) | (*inCell << 4)];
    }

    // last char
    *outCell = resultArray[(*LN + *BLN + *BN) | (*inCell << 4)];

    // centre rows
    inCell++; outCell++; LN++; BLN++; BN++; BRN++; RN++;
    int* TN = inCell - GRID_WIDTH;
    int* TLN = TN - 1;
    int* TRN = TN + 1;
    int* innerRowEnd = inCell + GRID_WIDTH * (GRID_HEIGHT - 2); // subtract 2 to account for first and last rows
    for (; inCell < innerRowEnd; ++inCell, ++outCell, ++TN, ++TLN, ++LN, ++BLN, ++BN, ++BRN, ++RN, ++TRN)
    {
        // first char
        *outCell = resultArray[(*BN + *BRN + *RN + *TRN + *TN) | (*inCell << 4)];

        // loop through centre chars
        end = inCell + GRID_WIDTH - 1;
        inCell++; outCell++; TN++, TLN++, LN++, BLN++, BN++, BRN++, RN++, TRN++;
        for (; inCell < end; ++inCell, ++outCell, ++TN, ++TLN, ++LN, ++BLN, ++BN, ++BRN, ++RN, ++TRN)
        {
            *outCell = resultArray[(*TN + *TLN + *LN + *BLN + *BN + *BRN + *RN + *TRN) | (*inCell << 4)];
        }        

        // last chars
        *outCell = resultArray[(*TN + *TLN + *LN + *BLN + *BN) | (*inCell << 4)];
    }

    // last row
    // first char
    *outCell = resultArray[(*TN + *TRN + *RN) | (*inCell << 4)];

    // middle cols
    end = inCell + GRID_WIDTH - 1;
    inCell++; outCell++; TN++, TLN++, LN++, RN++, TRN++;
    for (; inCell < end; ++inCell, ++outCell, ++TN, ++TLN, ++LN, ++RN, ++TRN)
    {
        *outCell = resultArray[(*LN + *TLN + *TN + *TRN + *RN) | (*inCell << 4)];
    }

    // last char
    *outCell = resultArray[(*LN + *TLN + *TN) | (*inCell << 4)];
}

// Function:    swapPointers
// Description: Swaps two pointers.
// Parameters:
//      left:   Pointer to first pointer to swap (referred to as left)
//      right:  Pointer to second pointer to swap (referred to as right)
// Returns:     No Return
void swapPointers(int **left, int **right)
{
    int *tmp = *left;
    *left = *right;
    *right = tmp;
}

// Main
int main()
{
    // TODO: Change app loop to allow for exiting
    srand(time(0));
    int grid[GRID_HEIGHT * GRID_WIDTH] = { 0 };
    int buff[GRID_HEIGHT * GRID_WIDTH] = { 0 };
    int *gPtr = grid;
    int *bPtr = buff;
    populateGrid(gPtr);
    for (int i = 0; i < 100; i++)
    {
        displayGrid(gPtr);
        tickGrid(gPtr, bPtr);
        swapPointers(&gPtr, &bPtr);
        printf("\nPress ENTER key to tick...");
        getc(stdin);
        system("cls");
    }
}


