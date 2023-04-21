//
//  functions.h
//  HW3
//
//  Created by Jesus Alfonso Robles on 4/20/23.
//  Copyright © 2023 Jesus Alfonso Robles. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include "functions.h"
#include <stdio.h>
#include <vector>
#include <algorithm>


typedef struct board {
    int availableMoves[4];
    int solutions[35];
    char string[10];
    int depth;
    int blank;
    int columns;
    int rows;
    int prev;
    int fn;
} board;

// sorts boards based on fn value
bool compareByFn(const board* a, board* b);

// constructor for a new board with string row and column parameters
board* newBoard(int rows, int columns, char* string);

// checks that the initial and final state are in the right format
bool verifyInput(char* string);


// updates the blank tile location
void updateBlank(board* currState);

// determines which moves a board state can make
void availableMoves(board* currState);

// determines the number of misplaced tiles by comparing two boards
int numMisplaced(board* currState, board* goalState);

// updates a board after a move (0, 1, 2 or 3)
void moveTile(board* currState, int move, int depth);

// prints values of string in a matrix form
void printMatrix(board* tempBoard);

// makes sure the user enters a valid option
char optionSelect();

// takes input from keyboard and returns string with matrix values
char* takeInput();

// updates the fn value for a current state
void updateFnMisplacedTiles(board* currState, board* goalState);

// removes a board from the queue
void removeBoard(board* currState, std::vector<board*> &queue);

// checks if a board state has already been visited
int checkVisited(board* currState, std::vector<board*> visited);

void updateSolutions(board* currstate, board* prevState, int move);

// prints solution and results
void printResults(board* bestState, int iteration, int nodes);

// applies the Misplaced Tiles Heuristic and prints results
int misplacedTiles(board* initState, board* goalState);

void updateFnManhattanDistance(board* currState, board* goalState);

// applies the Manhattan Distance Heuristic and prints results
int manhattanDistance(board* initState, board* goalState);

#endif /* functions_h */
