/*
Implementation file of the Board class for the Chain Reaction game. Reads from a file 
and sets up the board, validates and places chains on the board, prints board, and checks win.
*/

#include "Board.h"
#include "GridPosition.h"
#include "BoardMaker.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

/* Parameterized constructor that reads in the string filename, opens the file, and dynamically allocates 
   memory for the board */
Board::Board(string filename) {
    
    // Dynamically allocates memory for the board. 
    board = new GridPosition*[10];
    for (int i = 0; i < 10; i++) {
        board[i] = new GridPosition[10];
    }

    // Opens the file
    ifstream inFile(filename);

    // Reads each line from the file and sets the nodes
    string line;
    for (int i = 0; i < 10; i++) {
        getline(inFile, line);
        for (int j = 0; j < 10; j++) {
            board[i][j].setNode(line[j]);
        }
    }

    // Close the file
    inFile.close();

    // Sets each node numbers to the number of chains it's connected to
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j].getNode() == '0') {
                int chain_count = countChains(i, j);
                board[i][j] = board[i][j] + chain_count;
            }
        }
    }

    // Removes all of the chains from the board so it's ready to play
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j].isChain()) {
                board[i][j].setNode('.');
            }
        }
    }
}

// Default constructor that dynamically allocates an empty board
Board::Board() {
    // Dynamically allocates an empty board
    board = new GridPosition*[10];
    for (int i = 0; i < 10; i++) {
        board[i] = new GridPosition[10];
    }

    // Makes the board empty by setting each node to '.'
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j].setNode('.');
        }
    }
}

// Takes in a boolean, initializes the board, and uses BoardMaker to fill the board randomly. 
Board::Board(bool ec) {
    srand(time(0));
    
    // Dynamically allocates memory for the board.
    board = new GridPosition*[10];
    for (int i = 0; i < 10; i++) {
        board[i] = new GridPosition[10];
    }
    
    // Initializes the board
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j].setNode('.');
        }
    }
    
    // Sets a random node in the center and then sets up board
    int center_row = BoardMaker::randomNum(4,5);
    int center_col = BoardMaker::randomNum(4,5);
    board[center_row][center_col].setNode('0');
    BoardMaker::setUpBoard(center_row, center_col, board);
    
    // Sets each node numbers to the number of chains it's connected to
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j].getNode() == '0') {
                int chain_count = countChains(i, j);
                board[i][j] = board[i][j] + chain_count;
            }
        }
    }
    
    // Removes all of the chains from the board so it's ready to play
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j].isChain()) {
                board[i][j].setNode('.');
            }
        }
    }
}

// Destructor to free the memory of each row and then the board
Board::~Board() {
    // Frees the memory of each row
    for (int i = 0; i < 10; i++) {
        delete[] board[i];
    }
    // Frees the memory of the 2d array board
    delete[] board;
}

// Function to run the game
void Board::runGame() {
    // User input variable
    string user_input;
    
    printBoard();
    
    // While loop until the user wins.
    while (checkWin() == false) {
        
        // Takes user input
        cout << "Enter a row, a column, a space, and a cardinal direction (e.g. AK n): ";
        getline(cin, user_input);
        cout << "\n";
        
        // Capitalizes the row and column
        user_input[0] = toupper(user_input[0]);
        user_input[1] = toupper(user_input[1]);
        
        // Validates user input
        while (validChain(user_input) == false) {
            cout << "Enter a row, a column, a space, and a cardinal direction (e.g. AK n): ";
            getline(cin, user_input);
            cout << "\n";
            user_input[0] = toupper(user_input[0]);
            user_input[1] = toupper(user_input[1]);
        }
        
        // Places the chains and prints board
        placeChains(user_input);
        printBoard();
    }
    cout << "Congratulations! You have connected all the nodes!\n";
}

/* Function to count and return how many chains are connected to a node as helper for setting up the 
   board after reading it from the file */
int Board::countChains(int r, int c) {
    // Variable to keep track of the number of chains
    int chain_count = 0;

    // Checks if there is a chain above the node and increments chain_count
    if (r > 0 && board[r - 1][c].isChain()) {
        char chain = board[r - 1][c].getNode();
        if (chain == '|') {
            chain_count += 1;
        } 
        else if (chain == 'H') {
            chain_count += 2;
        }
    }

    // Checks if there is a chain below the node and increments chain_count
    if (r < 9 && board[r + 1][c].isChain()) {
        char chain = board[r + 1][c].getNode();
        if (chain == '|') {
            chain_count += 1;
        } 
        else if (chain == 'H') {
            chain_count += 2;
        }
    }

    // Checks if there is a chain left of the node and increments chain_count
    if (c > 0 && board[r][c - 1].isChain()) {
        char chain = board[r][c - 1].getNode();
        if (chain == '-') {
            chain_count += 1;
        } 
        else if (chain == '=') {
            chain_count += 2;
        }
    }

    // Checks if there is a chain right of the node and increments chain_count
    if (c < 9 && board[r][c + 1].isChain()) {
        char chain = board[r][c + 1].getNode();
        if (chain == '-') {
            chain_count += 1;
        } else if (chain == '=') {
            chain_count += 2;
        }
    }

    return chain_count;
}

/* Function to check if the game has been won.
   This function uses countChains to determine whether the number of chains attached to every 
   node on the board matches the number of that node, returning true if that’s the case and false 
   otherwise */
bool Board::checkWin() {
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j].getNode() >= '1' && board[i][j].getNode() <= '8') {
                // Variable of number of chains connected to node
                int chain_count = countChains(i, j);
                // Returns false if number doesn't match node
                if (chain_count != (board[i][j].getNode() - '0')) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

/* Function to make sure a chain builds correctly, used during input validation.
   This function passes the user input as a string and returns false if placing chains based on that 
   input would go off the board without hitting a node or cross over an existing chain, otherwise it 
   returns true */
bool Board::validChain(string input) {
    
    // Validates input length
    if (input.length() < 4 || input.length() > 4) {
        cout << "Invalid input. Too many or too few characters.\n";
        return false;
    }

    // Converts row letter and column letter to index and assign dir to the cardinal direction
    int row = input[0] - 'A';
    int col = input[1] - 'K';
    char direction = input[3];

    // Validates row and column
    if (row < 0 || row >= 10 || col < 0 || col >= 10) {
        cout << "Invalid input. Row must be A-J and column must be K-T.\n";
        return false;
    }

    // Validates if the position is a node
    if (board[row][col].getNode() < '1' || board[row][col].getNode() > '8') {
        cout << "Invalid input. There is no node at that location.\n";
        return false;
    }

    // Validates direction and checks if space is between column and direction
    if ((direction != 'n' && direction != 's' && direction != 'e' && direction != 'w') || input[2] != ' ') {
        cout << "Invalid input. Direction must be n, e, s, or w and there must be a space between the column and direction.\n";
        return false;
    }

    // Variables used for determining if chain can be placed at the direction
    int direction_row = 0;
    int direction_col = 0;
    
    if (direction == 'n') {
        direction_row = -1;
    }
    else if (direction == 's') {
        direction_row = 1;
    }
    else if (direction == 'e') {
        direction_col = 1;
    }
    else if (direction == 'w') {
        direction_col = -1;
    }
    
    int row1 = row + direction_row;
    int col1 = col + direction_col;
    
    // Boolean variable, true means node is in direction path and false means it's not
    bool node_on_path = false;
    
    // While loop to check if node is on direction path
    while (node_on_path == false && row1 >= 0 && row1 < 10 && col1 >= 0 && col1 < 10) {
        if (board[row1][col1].getNode() >= '1' && board[row1][col1].getNode() <= '8') {
            node_on_path = true;
        }
        else {
            row1 += direction_row;
            col1 += direction_col;
        }
    }
    
    // Returns false if path is blocked or goes off the board
    if (node_on_path == false) {
        cout << "Invalid input. That path is blocked or goes off the board.\n";
        return false;
    }
    
    return true;
}

// Function to take the user input as a string and place chains onto the board accordingly
void Board::placeChains(string input) {
    
    // Converts row letter and column letter to index and assign dir to the cardinal direction
    int row = input[0] - 'A';
    int col = input[1] - 'K';
    char direction = input[3];

    // Determine the direction of movement
    int direction_row = 0;
    int direction_col = 0;
    if (direction == 'n') {
        direction_row = -1;
    }
    else if (direction == 's') {
        direction_row = 1;
    }
    else if (direction == 'e') {
        direction_col = 1;
    }
    else if (direction == 'w') {
        direction_col = -1;
    }

    // Places chains
    int r = row + direction_row;
    int c = col + direction_col;
    
    // Boolean variable, true if node is reached and false if not
    bool node_reached = false;
    
    // While loop until a node is reached
    while (node_reached == false && r >= 0 && r < 10 && c >= 0 && c < 10) {
        if (board[r][c].getNode() >= '1' && board[r][c].getNode() <= '8') {
            node_reached = true;
        } 
        else {
            if (direction == 'n' || direction == 's') {
                
                if (board[r][c].getNode() == '.') {
                    board[r][c].setNode('|');
                }
                else if (board[r][c].getNode() == '|') {
                    board[r][c].setNode('H');
                }
                else if (board[r][c].getNode() == 'H') {
                    board[r][c].setNode('.');
                }
            } 
            else {
                
                if (board[r][c].getNode() == '.') {
                    board[r][c].setNode('-');
                }
                else if (board[r][c].getNode() == '-') {
                    board[r][c].setNode('=');
                }
                else if (board[r][c].getNode() == '=') {
                    board[r][c].setNode('.');
                }
            }
            
            r += direction_row;
            c += direction_col;
        }
    }
}

// Function to print the board with its labels
void Board::printBoard() {
    
    cout << "    K L M N O P Q R S T" << "\n";
    cout << "  ---------------------" << "\n";

    // Prints each row
    for (int i = 0; i < 10; i++) {
        cout << static_cast<char>('A' + i) << " | ";
        for (int j = 0; j < 10; j++) {
            cout << board[i][j].getNode();
            if (j < 9) {
                cout << " ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}


