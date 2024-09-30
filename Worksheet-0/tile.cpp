#include "tile.hpp"

Tile::Tile(int val){
    state = val;
} 

int Tile::getState(){
    return state;
}

bool Tile::setState(int val){
    if (state == 0){
        state = val;
        return true;
    }
    return false;
}

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