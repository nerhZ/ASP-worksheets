#include "tile.hpp"

Tile::Tile(int val){
    state = val;
} 

int Tile::getState(){
    return state;
}

// Only allow the state to be set if the current state is 0 (don't allow moves to be overwritten)
bool Tile::setState(int val){
    if (state == 0){
        state = val;
        return true;
    }
    return false;
}

// Get the character for the state of the tile (player 1 or player 2)
char Tile::getStateChar(){
    switch(state){
        case 0:
            return ' ';
            break;
        case 1:
            return 'X';
            break;
        case 2:
            return 'O';
            break;
        default:
            return ' ';
            break;
    }
}