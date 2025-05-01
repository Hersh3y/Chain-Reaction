/*
Implementation file of the GridPosition class.
Represents each position on the game board and handles node and chain.
*/

#include "GridPosition.h"
#include <iostream>
#include <string>
using namespace std;

// Default constructor, sets the node char to an empty space (‘.’)
GridPosition::GridPosition() {
    node = '.';
}

// Parameterized constructor, sets the node char to the passed character
GridPosition::GridPosition(char n) {
    node = n;
}

// Sets the node char to the passed character
void GridPosition::setNode(char n) {
    node = n;
}

// Returns the node char
char GridPosition::getNode() {
    return node;
}

// Returns true if the node char is ‘-’, ‘=’, ‘|’, or ‘H’ and false otherwise
bool GridPosition::isChain() {
    bool is_chain = (node == '-' || node == '=' || node == '|' || node == 'H');
    return is_chain;
}

/* If the node char is a number, increases it by the passed int but returns a new GridPosition 
   instead of modifying the current one */
GridPosition GridPosition::operator+(int n) {
    if (node >= '0' && node <= '8') {
        int num = (node - '0') + n;
        if (num >= 0 && num <= 8) {
            return GridPosition('0' + num);
        }
    }
    return *this;
}

/* If the node char is a number, decreases it by the passed int but returns a new GridPosition 
   instead of modifying the current one */
GridPosition GridPosition::operator-(int n) {
    if (node >= '0' && node <= '8') {
        int num = (node - '0') - n;
        if (num >= 0 && num <= 8) {
            return GridPosition('0' + num);
        }
    }
    return *this;
}

// If the node char is a number, increases it by one
GridPosition GridPosition::operator++() {
    if (node >= '0' && node <= '8') {
        int num = (node - '0') + 1;
        if (num <= 8) {
            node = '0' + num;
        }
    }
    return *this;
}

/* If the node char is a number, increases it by one but returns the GridPosition with the 
   original char */
GridPosition GridPosition::operator++(int) {
    GridPosition original = *this;
    ++(*this);
    return original;
}

// If the node char is a number, decreases it by one
GridPosition GridPosition::operator--() {
    if (node >= '0' && node <= '8') {
        int num = (node - '0') - 1;
        if (num >= 0) {
            node = '0' + num;
        }
    }
    return *this;
}

/* If the node char is a number, decreases it by one but returns the GridPosition with the 
   original char */
GridPosition GridPosition::operator--(int) {
    GridPosition original = *this;
    --(*this);
    return original;
}



