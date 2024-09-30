#include "tile.hpp"
#include "board.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

// Hard-coded list of valid tiles, used for checking if user input is correct (and also generating map of tiles)
std::string validTiles[9] = {"A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3"};

// Function to validate whether user's input matches a real tile
bool validateTile(std::string chosenTile){
    for(std::string tile : validTiles){
        if (chosenTile == tile){
            return true;
        }
    }
    return false;
}

int main(){
    // Create a map of tiles for the board
    std::map<std::string, Tile> tiles;
    // Loop through each valid tile and initialise a tile to the corresponding key
    for (std::string tile : validTiles){
        tiles[tile] = Tile();
    }
    // Initialise the playing board
    Board board;

    // Logic for playing the game
    while (true){
        int currentPlayer = board.getPlayer();
        board.outputBoard(tiles);

        std::string chosenTile;

        std::cout << "Player " << currentPlayer << ", please enter a tile" << std::endl;
        std::cin >> chosenTile; 

        // Converts user's tile input to uppercase
        transform(chosenTile.begin(), chosenTile.end(), chosenTile.begin(), ::toupper);

        if (!validateTile(chosenTile)){
            std::cout << "Chosen tile does not exist. Please try again." << std::endl;
            continue;
        }

        // Set the state of the chosen tile using the current player
        bool success = tiles[chosenTile].setState(board.getPlayer());
        // If the tile is occuppied then let them know it cannot be changed
        if (!success){
            std::cout << "This tile is already occuppied. Please try again" << std::endl;
        }
        // Check if a win condition has been met.
        // 0 == continue
        int winCheck = board.checkWin(tiles);
        // 1 == win
        if ( winCheck == 1){
            std::cout << "Player " << currentPlayer << " has won!" << std::endl;
            break;
        // 2 == draw
        } else if ( winCheck == 2){
            std::cout << "No tiles remaining. Match has concluded in a draw." << std::endl;
            break;
        }
        // Flip the turn (ensure the board is up to date with the player to move next)
        board.flipTurnFlag();
    }

    // Print final state of board
    board.outputBoard(tiles);
    return 0;
};