#include "tile.hpp"
#include <iostream>

void outputBoard(Tile* tiles){
    std::cout << tiles[0].getStateStr() << " | " << tiles[1].getStateStr() << " | " << tiles[2].getStateStr() << "\n";
    std::cout << tiles[3].getStateStr() << " | " << tiles[4].getStateStr() << " | " << tiles[5].getStateStr() << "\n";
    std::cout << tiles[6].getStateStr() << " | " << tiles[7].getStateStr() << " | " << tiles[8].getStateStr() << "\n";
};

int main(){
    // Create an array of tiles - require 9 to make a tic tac toe board
    Tile tiles[9];

    Tile* tilesPtr = tiles;

    bool playing = true;
    while (playing){
        outputBoard(tilesPtr);
        playing = false;
    }


    return 0;
};