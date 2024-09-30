#include "tile.hpp"
#include "board.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

std::string validTiles[9] = {"A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3"};

bool validateTile(std::string chosenTile){
    for(std::string tile : validTiles){
        // std::cout << tile << " " << chosenTile << std::endl;
        if (chosenTile == tile){
            return true;
        }
    }
    return false;
}

int main(){
    // Create a map of tiles for the board
    std::map<std::string, Tile> tiles;
    for (std::string tile : validTiles){
        tiles[tile] = Tile();
    }
    // Initialise the playing board
    Board board;

    // Logic for playing the game
    while (true){
        board.outputBoard(tiles);

        std::string chosenTile;

        std::cout << "Please enter a tile" << std::endl;
        std::cin >> chosenTile; 

        // Converts input to uppercase
        transform(chosenTile.begin(), chosenTile.end(), chosenTile.begin(), ::toupper);

        if (!validateTile(chosenTile)) continue;
        bool success = tiles[chosenTile].setState(board.getPlayer());
        if (!success){
            std::cout << "This tile is already occuppied. Please try again" << std::endl;
        }
        int winCheck = board.checkWin(tiles);
        if ( winCheck == 1){
            std::cout << "Player " << board.getPlayer() << " has won!" << std::endl;
            break;
        } else if ( winCheck == 2){
            std::cout << "No tiles remaining. Match has concluded in a draw." << std::endl;
            break;
        }
        board.flipTurnFlag();
    }

    return 0;
};