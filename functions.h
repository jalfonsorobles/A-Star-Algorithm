//
//  functions.h
//  ECE479_hw3
//
//  Created by Jesus Alfonso Robles on 3/19/20.
//  Copyright © 2020 Jesus Alfonso Robles. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <stdlib.h>
#include <string.h>
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
bool compareByFn(const board* a, board* b) {
    return a->fn < b->fn;
}

// constructor for a new board with string row and column parameters
board* newBoard(int rows, int columns, char* string) {
    board* newBoard = (board*) malloc(sizeof(board));
    strcpy(newBoard->string, string);
    newBoard->depth = 0;
    newBoard->blank = -1;
    newBoard->columns = columns;
    newBoard->rows = rows;
    newBoard->prev = -1;
    newBoard->fn = 15;
    
    // initializing the moves to -1 (LEFT, RIGHT, UP, DOWN), where
    // the indices represent these moves: index 0 is LEFT, index 1 is RIGHT
    // index 2 is UP and index DOWN is 3.
    for (int i = 0; i < 4 ; i++) {
        newBoard->availableMoves[i] = -1;
    }
    
    // moves required to get to this board from the initial state
    for (int i = 0; i < 35; i++) {
        newBoard->solutions[i] = -1;
    }
    return newBoard;
}

// updates the blank tile location
void updateBlank(board* currState) {
    
    for (int i = 0; i < strlen(currState->string); i++) {
        
        if (currState->string[i] == '_') {
            currState->blank = i;
            break;
        }
    }
}

// determines which moves a board state can make
void availableMoves(board* currState) {
    updateBlank(currState);
    
    if (currState->blank < 3) {
        // can move down
        currState->availableMoves[3] = 3;
    }
    
    else if (currState->blank > 2 && currState->blank < 6) {
        // can move up and down
        currState->availableMoves[2] = 2;
        currState->availableMoves[3] = 3;
    }
    
    else if (currState->blank > 5) {
        // can move up
        currState->availableMoves[2] = 2;
    }
    
    if (currState->blank == 0 || currState->blank == 3 || currState->blank == 6) {
        // can move right
        currState->availableMoves[1] = 1;
    }
    
    else if (currState->blank == 1 || currState->blank == 4 || currState->blank == 7) {
        // can move left and right
        currState->availableMoves[0] = 0;
        currState->availableMoves[1] = 1;
    }
    
    else if (currState->blank == 2 || currState->blank == 5 || currState->blank == 8) {
        // can move left
        currState->availableMoves[0] = 0;
    }
}

// determines the number of misplaced tiles by comparing two boards
int numMisplaced(board* currState, board* goalState) {
    int misplacedTiles = 0;
    
    for (int i = 0; i < strlen(currState->string); i++) {
        
        if (currState->string[i] != goalState->string[i] && currState->string[i] != '_') {
            misplacedTiles++;
        }
    }
    return misplacedTiles;
}

// updates a board after a move (0, 1, 2 or 3)
void moveTile(board* currState, int move, int depth) {
    updateBlank(currState);
    // get the char at index blank
    int blank = currState->blank;
    char swap;
    
    // if move is LEFT
    if (move == 0) {
        // get the char that will be swapped
        swap = currState->string[blank - 1];
        // place the '_' tile at new location (-1)
        currState->string[blank - 1] = currState->string[blank];
        // place the swapped char where the '_' used to be
        currState->string[blank] = swap;
        // update blank
        currState->blank = blank - 1;
        // update prev move to avoid returning there (cannot move RIGHT)
        currState->prev = 1;
        // update depth where this board is found
        currState->depth = depth;
    }
    
    // if move is RIGHT
    else if (move == 1) {
        // get the char that will be swapped
        swap = currState->string[blank + 1];
        // place the '_' tile at new location (+1)
        currState->string[blank + 1] = currState->string[blank];
        // place the swapped char where the '_' used to be
        currState->string[blank] = swap;
        // update blank
        currState->blank = blank + 1;
        // update prev move to avoid returning there (cannot move LEFT)
        currState->prev = 0;
        // update depth where this board is found
        currState->depth = depth;
    }
    
    // if move is UP
    else if (move == 2) {
        // get the char that will be swapped
        swap = currState->string[blank - 3];
        // place the '_' tile at new location (-3)
        currState->string[blank - 3] = currState->string[blank];
        // place the swapped char where the '_' used to be
        currState->string[blank] = swap;
        // update blank
        currState->blank = blank - 3;
        // update prev move to avoid returning there (cannot move DOWN)
        currState->prev = 3;
        // update depth where this board is found
        currState->depth = depth;
    }
    
    // if move is DOWN
    else if (move == 3) {
        // get the char that will be swapped
        swap = currState->string[blank + 3];
        // place the '_' tile at new location (+3)
        currState->string[blank + 3] = currState->string[blank];
        // place the swapped char where the '_' used to be
        currState->string[blank] = swap;
        // update blank
        currState->blank = blank + 3;
        // update prev move to avoid returning there (cannot move UP)
        currState->prev = 2;
        // update depth where this board is found
        currState->depth = depth;
    }
}

// prints values of string in a matrix form
void printMatrix(board* tempBoard) {
    printf("\n");
    
    for (int i = 0; i < strlen(tempBoard->string); i++) {
        printf("%c ", tempBoard->string[i]);
        
        if (i == 2 || i == 5) {
            printf("\n");
        }
    }
    printf("\n");
}

// makes sure the user enters a valid option
char optionSelect() {
    char option;
    scanf("%c", &option);
    
    while (option != 'a' && option != 'b' && option != 'A' && option != 'B') {
        printf("Enter valid option\n");
        fflush(stdin);
        scanf("%c", &option);
    }
    return option;
}

// takes input from keyboard and returns string with matrix values
char* takeInput() {
    char string1[20];
    char string2[10];
    int j = 0;
    
    // takes in first row with 3 columns
    fgets(string1, 6, stdin);
    // clear buffer
    fflush(stdin);
    // takes in second row with 3 columns
    fgets(string2, 6 , stdin);
    // clear buffer
    fflush(stdin);
    // concatenates two strings
    strcat(string1, string2);
    // takes in third row with 3 columns
    fgets(string2, 6, stdin);
    // clear buffer
    fflush(stdin);
    // concatenates two strings
    strcat(string1, string2);
    
    // loop used to remove 'space' from string
    for (int i = 0; i < strlen(string1); i++) {
        
        if (string1[i] != ' ' && string1[i] != '\n') {
            string2[j] = string1[i];
            j++;
        }
    }
    // must pass pointer with memory allocated
    char* string0 = (char*) malloc(sizeof(string2));
    strcpy(string0,string2);
    return string0;
}

// updates the fn value for a current state
void updateFnMisplacedTiles(board* currState, board* goalState) {
    currState->fn = numMisplaced(currState, goalState) + currState->depth;
}

// removes a board from the queue
void removeBoard(board* currState, std::vector<board*> &queue) {
    
    for (int i = 0; i < queue.size(); i++) {
        
        if (strcmp(currState->string, queue.at(i)->string) == 0) {
            queue.erase(queue.begin() + i);
            break;
        }
    }
}

// checks if a board state has already been visited
int checkVisited(board* currState, std::vector<board*> visited) {
    
    for (int i = 0; i < visited.size(); i++) {
        
        if (strcmp(visited.at(i)->string, currState->string) == 0) {
            return 1;
        }
    }
    return 0;
}

void updateSolutions(board* currstate, board* prevState, int move) {
    int i = 0;
    
    while (prevState->solutions[i] != -1) {
        currstate->solutions[i] = prevState->solutions[i];
        i++;
    }
    currstate->solutions[i] = move;
}

// prints solution and results
void printResults(board* bestState, int iteration, int nodes) {
    printf("\nSolution:\n");
    int i = 0;
    while (bestState->solutions[i] != -1) {
        printf("\nMove blank ");
        
        if (bestState->solutions[i] == 0) {
            printf("up");
        }
        
        else if (bestState->solutions[i] == 1) {
            printf("down");
        }
        
        else if (bestState->solutions[i] == 2) {
            printf("left");
        }
        
        else if (bestState->solutions[i] == 3) {
            printf("right");
        }
        i++;
    }
    printf("\n\nGiven the selected heuristic, the solution required %d moves.\nThe A* explored %d number of nodes to find this solution\nand went through %d iterations to find it\n\n\n", bestState->depth, nodes, iteration);
}

// applies the Misplaced Tiles Heuristic and prints results
int misplacedTiles(board* initState, board* goalState) {
    board* bestState = newBoard(initState->rows, initState->columns, initState->string);
    // queue of potential boards for future evaluation
    std::vector <board*> queue;
    std::vector <board*> visited;
    visited.push_back(initState);
    initState->depth = 0;
    updateBlank(initState);
    // used to measure depth of iteration
    int depth = 1;
    // current iteration to find optimal solution
    int iteration = 0;
    // number of nodes explored
    int nodes = 0;
    
    while (strcmp(bestState->string, goalState->string) != 0) {
        availableMoves(bestState);
        board* upState = newBoard(initState->rows, initState->columns, bestState->string);
        board* downState = newBoard(initState->rows, initState->columns, bestState->string);
        board* leftState = newBoard(initState->rows, initState->columns, bestState->string);
        board* rightState = newBoard(initState->rows, initState->columns, bestState->string);
        // establishes all values to a high value for comparison at end of iteration
        int fn[4] = {20000, 20000, 20000, 20000};
        
        for (int i = 0; i < 4; i++) {
            
            // make an available move
            if (bestState->availableMoves[i] == i) {
                
                if (i == 0 && bestState->prev != i) {
                    moveTile(leftState, i, depth);
                    
                    if (checkVisited(leftState, visited) == 0) {
                        updateSolutions(leftState, bestState, 2);
                        updateFnMisplacedTiles(leftState, goalState);
                        queue.push_back(leftState);
                        fn[i] = leftState->fn;
                    }
                }
                
                else if (i == 1 && bestState->prev != i) {
                    moveTile(rightState, i, depth);
                    
                    if (checkVisited(rightState, visited) == 0) {
                        updateSolutions(rightState, bestState, 3);
                        updateFnMisplacedTiles(rightState, goalState);
                        queue.push_back(rightState);
                        fn[i] = rightState->fn;
                    }
                }
                
                else if (i == 2 && bestState->prev != i) {
                    moveTile(upState, i, depth);
                    
                    if (checkVisited(upState, visited) == 0) {
                        updateSolutions(upState, bestState, 0);
                        updateFnMisplacedTiles(upState, goalState);
                        queue.push_back(upState);
                        fn[i] = upState->fn;
                    }
                }
                
                else if (i == 3 && bestState->prev != i) {
                    moveTile(downState, i, depth);
                    
                    if (checkVisited(downState, visited) == 0) {
                        updateSolutions(downState, bestState, 1);
                        updateFnMisplacedTiles(downState, goalState);
                        queue.push_back(downState);
                        fn[i] = downState->fn;
                    }
                }
            }
        }
        // sort queue by assending order of fn values
        std::sort(queue.begin(), queue.end(), compareByFn);
        
        if (fn[0] <= fn[1]  && fn[0] <= fn[2] && fn[0] <= fn[3] && fn[0] <= queue.at(0)->fn) {
            bestState = leftState;
            visited.push_back(leftState);
            removeBoard(leftState, queue);
            depth++;
        }
        
        else if (fn[1] <= fn[0]  && fn[1] <= fn[2] && fn[1] <= fn[3] && fn[1] <= queue.at(0)->fn) {
            bestState = rightState;
            visited.push_back(rightState);
            removeBoard(rightState, queue);
            depth++;
        }
        
        else if (fn[2] <= fn[0]  && fn[2] <= fn[1] && fn[2] <= fn[3] && fn[2] <= queue.at(0)->fn) {
            bestState = upState;
            visited.push_back(upState);
            removeBoard(upState, queue);
            depth++;
        }
        
        else if (fn[3] <= fn[0]  && fn[3] <= fn[1] && fn[3] <= fn[2] && fn[3] <= queue.at(0)->fn) {
            bestState = downState;
            visited.push_back(downState);
            removeBoard(downState, queue);
            depth++;
        }
        
        else {
            bestState = queue.at(0);
            visited.push_back(queue.at(0));
            removeBoard(queue.at(0), queue);
            depth = bestState->depth + 1;
        }
        
        if (depth > 20000) {
            printf("\nFor the above combination of the initial/goal states, there is no solution.\n\n\n");
            return 1;
        }
        iteration++;
    }
    nodes = int(queue.size() + visited.size());
    printResults(bestState, iteration, nodes);
    return 0;
}

void updateFnManhattanDistance(board* currState, board* goalState) {
    int distance = 0;
    int x1, y1, x2, y2 = 0;

        // finding x- and y- coordinates for goal state index
        for (int i = 0; i < strlen(goalState->string); i++) {
            
            if (goalState->string[i] == '_') {
                continue;
            }
            
            if (i == 0 || i ==  3 || i == 6) {
                x1 = 0;
            }
            
            else if (i == 1 || i == 4 || i == 7) {
                x1 = 1;
            }
            
            else {
                x1 = 2;
            }
            
            if (i < 3) {
                y1 = 0;
            }
            
            else if (i > 2 && i < 6) {
                y1 = 1;
            }
            
            else {
                y1 = 2;
            }
            
            // finding x- and y- coordinates for current state index
            for (int j = 0; j < strlen(currState->string); j++) {
                
                if (j == 0 || j ==  3 || j == 6) {
                    x2 = 0;
                }
                
                else if (j == 1 || j == 4 || j == 7) {
                    x2 = 1;
                }
                
                else {
                    x2 = 2;
                }
                
                if (j < 3) {
                    y2 = 0;
                }
                
                else if (j > 2 && j < 6) {
                    y2 = 1;
                }
                
                else {
                    y2 = 2;
                }
                
                // check for a match
                if (currState->string[j] == goalState->string[i]) {
                    distance += (abs(x1 - x2) + abs(y1 - y2));
                    continue;
                }
            }
        }
    currState->fn = distance + currState->depth;
}

// applies the Manhattan Distance Heuristic and prints results
int manhattanDistance(board* initState, board* goalState) {
    board* bestState = newBoard(initState->rows, initState->columns, initState->string);
    // queue of potential boards for future evaluation
    std::vector <board*> queue;
    std::vector <board*> visited;
    visited.push_back(initState);
    initState->depth = 0;
    updateBlank(initState);
    // used to measure depth of iteration
    int depth = 1;
    // current iteration to find optimal solution
    int iteration = 0;
    // number of nodes explored
    int nodes = 0;
    
    while (strcmp(bestState->string, goalState->string) != 0) {
        availableMoves(bestState);
        board* upState = newBoard(initState->rows, initState->columns, bestState->string);
        board* downState = newBoard(initState->rows, initState->columns, bestState->string);
        board* leftState = newBoard(initState->rows, initState->columns, bestState->string);
        board* rightState = newBoard(initState->rows, initState->columns, bestState->string);
        // establishes all values to a high value for comparison at end of iteration
        int fn[4] = {20000, 20000, 20000, 20000};
        
        for (int i = 0; i < 4; i++) {
            
            // make an available move
            if (bestState->availableMoves[i] == i) {
                
                if (i == 0 && bestState->prev != i) {
                    moveTile(leftState, i, depth);
                    
                    if (checkVisited(leftState, visited) == 0) {
                        updateSolutions(leftState, bestState, 2);
                        updateFnManhattanDistance(leftState, goalState);
                        queue.push_back(leftState);
                        fn[i] = leftState->fn;
                    }
                }
                
                else if (i == 1 && bestState->prev != i) {
                    moveTile(rightState, i, depth);
                    
                    if (checkVisited(rightState, visited) == 0) {
                        updateSolutions(rightState, bestState, 3);
                        updateFnManhattanDistance(rightState, goalState);
                        queue.push_back(rightState);
                        fn[i] = rightState->fn;
                    }
                }
                
                else if (i == 2 && bestState->prev != i) {
                    moveTile(upState, i, depth);
                    
                    if (checkVisited(upState, visited) == 0) {
                        updateSolutions(upState, bestState, 0);
                        updateFnManhattanDistance(upState, goalState);
                        queue.push_back(upState);
                        fn[i] = upState->fn;
                    }
                }
                
                else if (i == 3 && bestState->prev != i) {
                    moveTile(downState, i, depth);
                    
                    if (checkVisited(downState, visited) == 0) {
                        updateSolutions(downState, bestState, 1);
                        updateFnManhattanDistance(downState, goalState);
                        queue.push_back(downState);
                        fn[i] = downState->fn;
                    }
                }
            }
        }
        // sort queue by assending order of fn values
        std::sort(queue.begin(), queue.end(), compareByFn);
        
        if (fn[0] <= fn[1]  && fn[0] <= fn[2] && fn[0] <= fn[3] && fn[0] <= queue.at(0)->fn) {
            bestState = leftState;
            visited.push_back(leftState);
            removeBoard(leftState, queue);
            depth++;
        }
        
        else if (fn[1] <= fn[0]  && fn[1] <= fn[2] && fn[1] <= fn[3] && fn[1] <= queue.at(0)->fn) {
            bestState = rightState;
            visited.push_back(rightState);
            removeBoard(rightState, queue);
            depth++;
        }
        
        else if (fn[2] <= fn[0]  && fn[2] <= fn[1] && fn[2] <= fn[3] && fn[2] <= queue.at(0)->fn) {
            bestState = upState;
            visited.push_back(upState);
            removeBoard(upState, queue);
            depth++;
        }
        
        else if (fn[3] <= fn[0]  && fn[3] <= fn[1] && fn[3] <= fn[2] && fn[3] <= queue.at(0)->fn) {
            bestState = downState;
            visited.push_back(downState);
            removeBoard(downState, queue);
            depth++;
        }
        
        else {
            bestState = queue.at(0);
            visited.push_back(queue.at(0));
            removeBoard(queue.at(0), queue);
            depth = bestState->depth + 1;
        }
        
        if (depth > 20000) {
            printf("\nFor the above combination of the initial/goal states, there is no solution within a depth of 20000.\n\n\n");
            return 1;
        }
        iteration++;
    }
    nodes = int(queue.size() + visited.size());
    printResults(bestState, iteration, nodes);
    return 0;
}

#endif /* functions_h */
