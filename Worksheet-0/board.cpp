#include "board.hpp"
#include "tile.hpp"
#include <iostream>

// turnFlag used to decide which player's turn it is, will be converted from bool into 1 or 2 for case handling
Board::Board(bool val){
    turnFlag = val;
};

// Function to print the state of the board
void Board::outputBoard(std::map<std::string, Tile>& tiles){
    std::cout << tiles["A1"].getStateChar() << " | " << tiles["A2"].getStateChar() << " | " << tiles["A3"].getStateChar() << std::endl;
    std::cout << tiles["B1"].getStateChar() << " | " << tiles["B2"].getStateChar() << " | " << tiles["B3"].getStateChar() << std::endl;
    std::cout << tiles["C1"].getStateChar() << " | " << tiles["C2"].getStateChar() << " | " << tiles["C3"].getStateChar() << std::endl;
};

bool Board::getTurn(){
    return turnFlag;
}

int Board::takeTurn(){
    bool turn = getTurn();

    int chosenTurn;
    if (turn){
        chosenTurn = 1;
    } else {
        chosenTurn = 2;
    }

    return chosenTurn;
};

void Board::flipTurnFlag(){
    turnFlag = !turnFlag;
}