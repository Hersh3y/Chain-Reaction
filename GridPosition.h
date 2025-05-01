/*
Header file that defines the GridPosition class.
*/

#ifndef GRIDPOSITION_H
#define GRIDPOSITION_H

#include <string>
using namespace std;

class GridPosition {
public:
    
    // Default constructor, sets the node char to an empty space (‘.’)
    GridPosition();
    
    // Parameterized constructor, sets the node char to the passed character
    GridPosition(char);
    
    // Sets the node char to the passed character
    void setNode(char);
    
    // Returns the node char
    char getNode();
    
    // Returns true if the node char is ‘-’, ‘=’, ‘|’, or ‘H’ and false otherwise
    bool isChain();
    
    /* If the node char is a number, increases it by the passed int but returns a new GridPosition 
       instead of modifying the current one */
    GridPosition operator+(int);
    
    /* If the node char is a number, decreases it by the passed int but returns a new GridPosition 
       instead of modifying the current one */
    GridPosition operator-(int);
    
    // If the node char is a number, increases it by one
    GridPosition operator++(void);
    
    /* If the node char is a number, increases it by one but returns the GridPosition with the 
       original char */
    GridPosition operator++(int);
    
    // If the node char is a number, decreases it by one
    GridPosition operator--(void);
    
    /* If the node char is a number, decreases it by one but returns the GridPosition with the 
       original char */
    GridPosition operator--(int);
    
private:

    // Member variable
    char node;

};

#endif


