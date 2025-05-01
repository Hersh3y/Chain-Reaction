/*
Main driver file for Chain Reaction game. 
Handles user input and runs the game by calling runGame().
*/

/*
Harshal Patel
03/12/2025
Project-2: Chain Reaction
Purpose: Code for a Chain Reaction game. A user is presented with a board that 
         has several nodes with numbers ranging from 1 to 8. The goal of the 
         game is for a user to connect all nodes with a series of chain links.
Citations: 
    I used this to learn how to convert a char type to int type: 
        https://www.geeksforgeeks.org/cpp-program-for-char-to-int-conversion/
I certify that I followed the collaboration policy.
*/

#include "Board.h"
#include "GridPosition.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    
    // Variables
    string file_name;
    ifstream inFile;
    
    cout << "Welcome to CPSC 1070 Chain Reaction!\n\n";
    cout << "The goal is to connect all of the nodes into a single connected group\n";
    cout << "by creating a series of chains between the nodes. The number of chains\n";
    cout << "coming off of an node must match the number on that node.\n\n";
    cout << "Enter the coordinates of the node you would like to connect and a direction.\n";
    cout << "If there is already a chain, a second chain will be added. If there are\n";
    cout << "already two chains, the chains will be removed.\n\n";
    
    // Prompts the user to enter the file name
    cout << "Please enter the name of the file you would like to use: ";
    getline(cin, file_name);
    
    inFile.open(file_name);
    
    // Program ends if file can't be opened
    if (!inFile) {
        cout << "Error opening file!\n";
    }
    else {
        
        inFile.close();
        cout << "\n";
        
        // Creates the board
        Board board(file_name);
    
        // Runs the game
        board.runGame();
    }

    return 0;
}



