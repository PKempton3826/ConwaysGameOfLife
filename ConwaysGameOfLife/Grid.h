// File:            Grid.h
// Project:         Conways Game of Life
// Programmer:      Philip Kempton
// First Version:   2026-02-07
// Description:     Contains Grid prototypes and constants for the ConwaysGameOfLife application.

#ifndef _GRID_H_
#define _GRID_H_

#include <stdio.h>
#include <stdlib.h>

// Grid dimension constants
#define GRID_HEIGHT 25
#define GRID_WIDTH 25

// Prototypes
void displayGrid(int* grid);
void populateGrid(int* grid);
void iterateGrid(int** gridIn, int** gridOut);
void swapPointers(int** left, int** right);

#endif // !_GRID_H_
