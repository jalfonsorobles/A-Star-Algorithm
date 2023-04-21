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

    printf("Enter initial state using numbers 1-8 & using [_ , *, or -] as the blank tile.\nEnter three numbers per row.\n");
    char* string = takeInput();
    
    while (verifyInput(string)!= true) {
        
        // clear string
        string[0] = '\0';
        string = takeInput();
    }
    
    board* initState = newBoard(rows, columns, string);
    printf("\nEnter goal state\n");
    string = takeInput();
    
    while (verifyInput(string)!= true) {
        string = takeInput();
    }
    
    board* goalState = newBoard(rows, columns, string);
    printf("\nSelect the heuristic\na) Number of misplaced tiles\nb) Manhattan distance\n\n");

    char option = optionSelect();
    
    while (option != 'A' && option != 'a' && option != 'B' && option != 'b') {
        printf("\nEnter a correct option\n");

        option = optionSelect();
    }

    if (option == 'a' || option == 'A') {
        return misplacedTiles(initState, goalState);
    }

    else if (option == 'b' || option == 'b'){
        return manhattanDistance(initState, goalState);
    }
    
    else {
        
    }
}
