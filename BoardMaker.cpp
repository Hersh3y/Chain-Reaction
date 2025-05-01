/*
Implementation file of the BoardMaker class. Randomly makes valid boards for the 
Chain Reaction game by using recusion and validating node's position.
*/

#include "BoardMaker.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// Function to recursively generate nodes and chains on an empty board.
void BoardMaker::setUpBoard(int r, int c, GridPosition** board) {
    
    // Array of cardinal directions
    char directions[] = {'n', 'e', 's', 'w'};
    
    // For loop that goes through each direction
    for (int i = 0; i < 4; i++) {
        
        // Variables for the current direction and random distance between 2 and 5
        char dir = directions[i];
        int distance = randomNum(2, 5);
        
        if (validNewNode(distance, dir, r, c, board)) {
            
            // Initializes and adjusts the new node's posititon
            int new_row = r;
            int new_col = c;
            if (dir == 'n') {
                new_row = r - distance;
            } 
            else if (dir == 'e') {
                new_col = c + distance;
            } 
            else if (dir == 's') {
                new_row = r + distance;
            } 
            else if (dir == 'w') {
                new_col = c - distance;
            }

            // Checks if new node is off the edge of the board or not
            if (new_row >= 0 && new_row < 10 && new_col >= 0 && new_col < 10) {
                
                // Checks if new node has neighbors
                if (noNeighbors(new_row, new_col, board)) {
                    
                    // Sets new node
                    board[new_row][new_col].setNode('0');
                    
                    // Initializes and adjusts row and column direction
                    int dir_r = 0;
                    int dir_c = 0;
                    if (dir == 'n') {
                        dir_r = -1;
                    }
                    else if (dir == 'e') {
                        dir_c = 1;
                    }
                    else if (dir == 's') {
                        dir_r = 1;
                    }
                    else if (dir == 'w') {
                        dir_c = -1;
                    }
                    
                    // Initializes current node's row and column
                    int current_row = r + dir_r;
                    int current_col = c + dir_c;
                    
                    // For loop to place chains
                    for (int i = 0; i < distance - 1; i++) {
                        
                        int random_num = randomNum(0, 1);
                        char chain = '.';
                        
                        if (dir == 'n' || dir == 's') {
                            if (random_num == 0) {
                                chain = '|';
                            }
                            else {
                                chain = 'H';
                            }
                        } 
                        else {
                            if (random_num == 0) {
                                chain = '-';
                            }
                            else {
                                chain = '=';
                            }
                        }
                        
                        if (board[current_row][current_col].getNode() == '.') {
                            board[current_row][current_col].setNode(chain);
                        }
                        
                        // Moves to another current position
                        current_row += dir_r;
                        current_col += dir_c;
                    }
                    
                    // Recursive call
                    setUpBoard(new_row, new_col, board);
                }
            }
        }
    }
}

// Returns a random integer between the first int and the second int, inclusive.
int BoardMaker::randomNum(int a, int b) {
    int random_num = a + rand() % (b - a + 1);
    return random_num;
}

/* Returns true if all four positions adjacent to the passed row and column are empty, false 
   otherwise. */
bool BoardMaker::noNeighbors(int r, int c, GridPosition** board) {
    
    if (r > 0 && board[r-1][c].getNode() != '.') {
        return false;
    }
    if (c < 9 && board[r][c+1].getNode() != '.') {
        return false;
    }
    if (r < 9 && board[r+1][c].getNode() != '.') {
        return false;
    }
    if (c > 0 && board[r][c-1].getNode() != '.') {
        return false;
    }
    
    return true;
}

/* Function used to check whether a new node is allowed to generate during setup.
   The function returns false if the new node would be generated off the edge of the board, generating 
   the node would cross over an existing node or chain, or the positions adjacent to where the node 
   would generate are not empty. */
bool BoardMaker::validNewNode(int dist, char dir, int r, int c, GridPosition** board) {
    
    // Variables for new row and column posititon
    int new_row;
    int new_col;
    // Determines direction
    switch (dir) {
        case 'n': 
            new_row = r - dist;
            new_col = c; 
            break;
        case 'e': 
            new_row = r; 
            new_col = c + dist; 
            break;
        case 's': 
            new_row = r + dist; 
            new_col = c; 
            break;
        case 'w': 
            new_row = r; 
            new_col = c - dist; 
            break;
        default: 
            return false;
    }
    
    // Checks if new node is off the edge of the board or not
    if (new_row < 0 || new_row >= 10 || new_col < 0 || new_col >= 10) {
        return false;
    }
    
    // Row and column direction variables
    int dir_r = 0;
    int dir_c = 0;
    // Determines direciton
    switch (dir) {
        case 'n': 
            dir_r = -1; 
            break;
        case 's': 
            dir_r = 1; 
            break;
        case 'e': 
            dir_c = 1; 
            break;
        case 'w': 
            dir_c = -1; 
            break;
    }
    
    // Current row and column variables
    int current_row = r;
    int current_col = c;
    // For loop that goes through path direction
    for (int i = 0; i < dist; i++) {
        
        current_row += dir_r;
        current_col += dir_c;
        
        // Checks if new node is off the edge of the board or not
        if (current_row < 0 || current_row >= 10 || current_col < 0 || current_col >=10)
            return false;
        
        // Checks if node is empty or not 
        if (i < dist - 1 && board[current_row][current_col].getNode() != '.')
            return false;
    }
    
    // Checks if new node has neighbors
    bool no_neighbors = noNeighbors(new_row, new_col, board);
    
    return no_neighbors;
}


