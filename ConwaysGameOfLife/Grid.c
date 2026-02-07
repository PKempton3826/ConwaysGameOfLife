// File:            Grid.c
// Project:         Conway's Game of Life
// Programmer:      Philip Kempton
// First Version:   2026-02-07
// Description:     Contains Grid functions for the ConwaysGameOfLife application.

#include "Grid.h"

// Function:    displayGrid
// Description: Displays a grid of ones and zeros as '0's and '-'s, respectively.
//              Displays 'x' for invalid cell data.
// Parameters: 
//      grid:   The grid to display
// Returns:     N/A
void displayGrid(int* grid)
{
    // formatted string for displaying a char with enough padding to take up 2 digits
    const char formattedCellStr[] = "%2c";
    for (int row = 0; row < GRID_HEIGHT; row++)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            switch (grid[(row * GRID_WIDTH) + col])
            {
            case 1:
                printf(formattedCellStr, '0');
                break;
            case 0:
                printf(formattedCellStr, '-');
                break;
            default:
                printf(formattedCellStr, 'x');
                break;
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
// Returns:     N/A
void populateGrid(int* grid)
{
    // randomly assign each cell as 0 or 1
    int* end = grid + (GRID_HEIGHT * GRID_WIDTH);
    for (int* cell = grid; cell != end; ++cell)
    {
        if ((rand() % 2) == 0)
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

// Function:        iterateGrid
// Description:     Iterates the grid.
//                  Utilizes lookup arrys, pointer arithmetic, bit shifting, and bitwise ORs for efficiency.
// Parameters:
//      gridIn:     Pointer to the input grid for calculating the next iteration
//      gridOut:    Pointer to the output grid for returning the newly calculated iteration
// Returns:         N/A
void iterateGrid(int* gridIn, int* gridOut)
{
    int* inCell = gridIn;
    int* outCell = gridOut;

    // lookup array for efficiency
    int resultArray[] = {
        0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, // no-man's-land, unused indices
        0, 0, 1, 1, 0, 0, 0, 0, 0
    };

    // first row, first cell
    //      [ x o o o ]
    //      [ o o o o ]
    //      [ o o o o ]
    //      [ o o o o ]
    int* BN = inCell + GRID_WIDTH;
    int* RN = inCell + 1;
    int* BRN = inCell + GRID_WIDTH + 1;
    *outCell = resultArray[(*BN + *BRN + *RN) | (*inCell << 4)];

    // first row, inner cells
    //      [ o x x o ]
    //      [ o o o o ]
    //      [ o o o o ]
    //      [ o o o o ]
    int* end = inCell + GRID_WIDTH - 1;
    inCell++; outCell++; BN++; BRN++; RN++;
    int* LN = inCell - 1;
    int* BLN = inCell + GRID_WIDTH - 1;
    for (; inCell < end; ++inCell, ++outCell, ++LN, ++BLN, ++BN, ++BRN, ++RN)
    {
        *outCell = resultArray[(*LN + *BLN + *BN + *BRN + *RN) | (*inCell << 4)];
    }

    // first row, last cell
    //      [ o o o x ]
    //      [ o o o o ]
    //      [ o o o o ]
    //      [ o o o o ]
    *outCell = resultArray[(*LN + *BLN + *BN) | (*inCell << 4)];

    // inner row cells
    //      [ o o o o ]
    //      [ x x x x ]
    //      [ x x x x ]
    //      [ o o o o ]
    inCell++; outCell++; LN++; BLN++; BN++; BRN++; RN++;
    int* TN = inCell - GRID_WIDTH;
    int* TLN = TN - 1;
    int* TRN = TN + 1;
    int* innerRowEnd = inCell + GRID_WIDTH * (GRID_HEIGHT - 2); // subtract 2 to account for first and last rows
    for (; inCell < innerRowEnd; ++inCell, ++outCell, ++TN, ++TLN, ++LN, ++BLN, ++BN, ++BRN, ++RN, ++TRN)
    {
        // inner rows, first cell
        //      [ o o o o ]
        //      [ x o o o ]
        //      [ x o o o ]
        //      [ o o o o ]
        *outCell = resultArray[(*BN + *BRN + *RN + *TRN + *TN) | (*inCell << 4)];

        // inner rows, inner cells
        //      [ o o o o ]
        //      [ o x x o ]
        //      [ o x x o ]
        //      [ o o o o ]
        end = inCell + GRID_WIDTH - 1;
        inCell++; outCell++; TN++, TLN++, LN++, BLN++, BN++, BRN++, RN++, TRN++;
        for (; inCell < end; ++inCell, ++outCell, ++TN, ++TLN, ++LN, ++BLN, ++BN, ++BRN, ++RN, ++TRN)
        {
            *outCell = resultArray[(*TN + *TLN + *LN + *BLN + *BN + *BRN + *RN + *TRN) | (*inCell << 4)];
        }

        // inner rows, last cell
        //      [ o o o o ]
        //      [ o o o x ]
        //      [ o o o x ]
        //      [ o o o o ]
        *outCell = resultArray[(*TN + *TLN + *LN + *BLN + *BN) | (*inCell << 4)];
    }

    // last row, first cell
    //      [ o o o o ]
    //      [ o o o o ]
    //      [ o o o o ]
    //      [ x o o o ]
    *outCell = resultArray[(*TN + *TRN + *RN) | (*inCell << 4)];

    // last row, inner cells
    //      [ o o o o ]
    //      [ o o o o ]
    //      [ o o o o ]
    //      [ o x x o ]
    end = inCell + GRID_WIDTH - 1;
    inCell++; outCell++; TN++, TLN++, LN++, RN++, TRN++;
    for (; inCell < end; ++inCell, ++outCell, ++TN, ++TLN, ++LN, ++RN, ++TRN)
    {
        *outCell = resultArray[(*LN + *TLN + *TN + *TRN + *RN) | (*inCell << 4)];
    }

    // last row, last cell
    //      [ o o o o ]
    //      [ o o o o ]
    //      [ o o o o ]
    //      [ o o o x ]
    *outCell = resultArray[(*LN + *TLN + *TN) | (*inCell << 4)];
}

// Function:    swapPointers
// Description: Swaps two pointers.
// Parameters:
//      left:   Pointer to first pointer to swap (referred to as left)
//      right:  Pointer to second pointer to swap (referred to as right)
// Returns:     N/A
void swapPointers(int** left, int** right)
{
    *left = (int*)((uintptr_t)*left ^ (uintptr_t)*right);
    *right = (int*)((uintptr_t)*left ^ (uintptr_t)*right);
    *left = (int*)((uintptr_t)*left ^ (uintptr_t)*right);
}
