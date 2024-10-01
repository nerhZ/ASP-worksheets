#include "board.hpp"
#include "tile.hpp"
#include <iostream>

// turnFlag used to decide which player's turn it is, will be converted from bool into 1 or 2 for case handling
Board::Board(bool val){
    turnFlag = val;
};

// Function to print the state of the board
void Board::outputBoard(std::map<std::string, Tile>& tiles){
    std::cout << "  A   B   C" << std::endl; 
    std::cout << "1 " << tiles["A1"].getStateChar() << " | " << tiles["B1"].getStateChar() << " | " << tiles["C1"].getStateChar() << std::endl;
    std::cout << "2 " << tiles["A2"].getStateChar() << " | " << tiles["B2"].getStateChar() << " | " << tiles["C2"].getStateChar() << std::endl;
    std::cout << "3 " << tiles["A3"].getStateChar() << " | " << tiles["B3"].getStateChar() << " | " << tiles["C3"].getStateChar() << std::endl;
};

bool Board::getTurn(){
    return turnFlag;
}

// Gets the current player's number based on the turnFlag
int Board::getPlayer(){
    bool turn = getTurn();

    int player;
    if (turn){
        player = 1;
    } else {
        player = 2;
    }

    return player;
};

void Board::flipTurnFlag(){
    turnFlag = !turnFlag;
}

// Must return an integer due to 3 states rather than 2. 0 = continue, 1 = winner, 2 = draw.
int Board::checkWin(std::map<std::string, Tile>& tiles){
    const int player = getPlayer();
    for (auto& row : winConditions){
        // If marked ticks up to 3 then the player matches 3 in a row.
        int marked = 0;
        for (auto& elem : row){
            if (tiles[elem].getState() == player) marked++;
        }
        if (marked == 3) return 1;
    }

    // If every tile is taken and no winner is found then return 2 for a draw.
    int drawCounter = 0;
    for (auto const& [key, val] : tiles){
        if (tiles[key].getState() != 0) drawCounter++;
    }

    if (drawCounter == 9) return 2;

    return 0;
}