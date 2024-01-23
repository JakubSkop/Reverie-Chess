#include "BoardComponent.hpp"
#include "BoardElement.hpp"


Element<BoardComponent> GameBoardBuilder::getObject(){
    return gameboard;
}

GameBoardBuilder::GameBoardBuilder(ChessBoard board, sf::Vector2f position, Resources resources){
    
    //Set up Tiles
    gameboard.DrawableComponent.Board = board;
    for (int i{0}; i < Constants::MAX_BOARD_SIZE; i++){

    };


}