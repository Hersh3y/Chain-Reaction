/*
Header file that defines the Board class.
*/

#ifndef BOARD_H
#define BOARD_H

#include "GridPosition.h"
#include "BoardMaker.h"
#include <string>
using namespace std;

class Board {
public:
    
    /* Parameterized constructor that reads in the string filename, opens the file, and dynamically allocates 
       memory for the board */
    Board(string);
    
    // Default constructor that dynamically allocates an empty board 
    Board();
    
    // Takes in a boolean, initializes the board, and uses BoardMaker to fill the board randomly
    Board(bool ec);
    
    // Destructor to free the memory of each row and then the board
    ~Board();
    
    // Function to run the game
    void runGame();
    
    /* Function to count and return how many chains are connected to a node as helper for setting up the 
       board after reading it from the file */
    int countChains(int r, int c);
    
    /* Function to check if the game has been won.
       This function uses countChains to determine whether the number of chains attached to every 
       node on the board matches the number of that node, returning true if that’s the case and false 
       otherwise */
    bool checkWin();
    
    /* Function to make sure a chain builds correctly, used during input validation.
       This function passes the user input as a string and returns false if placing chains based on that 
       input would go off the board without hitting a node or cross over an existing chain, otherwise it 
       returns true */
    bool validChain(string input);
    
    // Function to take the user input as a string and place chains onto the board accordingly
    void placeChains(string input);
    
    // Function to print the board with its labels
    void printBoard();
    
private:
    
    // 2D Array member variable
    GridPosition** board;
    
};

#endif



