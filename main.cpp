//
//  main.c
//  ECE479_hw3
//
//  Created by Jesus Alfonso Robles on 3/19/22.
//  Copyright © 2022 Jesus Alfonso Robles. All rights reserved.
//

#include "functions.h"
#define rows 3
#define columns 3

int main() {

    printf("Enter initial state\n");
    char* string = takeInput();
    board* initState = newBoard(rows, columns, string);
    printf("\nEnter goal state\n");
    string = takeInput();
    board* goalState = newBoard(rows, columns, string);

    printf("\nSelect the heuristic\na) Number of misplaced tiles\nb) Manhattan distance\n\n");

    char option = optionSelect();

    if (option == 'a' || option == 'A') {
        return misplacedTiles(initState, goalState);
    }

    else {
        return manhattanDistance(initState, goalState);
    }
}
