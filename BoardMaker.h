/*
Header file that defines the BoardMaker class.
*/

#ifndef BOARDMAKER_H
#define BOARDMAKER_H

#include "GridPosition.h"
using namespace std;

class BoardMaker {
public:

    // Function to recursively generate nodes and chains on an empty board. 
    static void setUpBoard(int r, int c, GridPosition** board);
    
    // Returns a random integer between the first int and the second int, inclusive.
    static int randomNum(int a, int b);
    
    /* Returns true if all four positions adjacent to the passed row and column are empty, false 
       otherwise. */
    static bool noNeighbors(int r, int c, GridPosition** board);
    
    /* Function used to check whether a new node is allowed to generate during setup.
       The function returns false if the new node would be generated off the edge of the board, generating 
       the node would cross over an existing node or chain, or the positions adjacent to where the node 
       would generate are not empty. */
    static bool validNewNode(int dist, char dir, int r, int c, GridPosition** board);

};

#endif



