#include "BoardComponent.hpp"
#include "BoardElement.hpp"

#include <algorithm>


Element<BoardComponent> GameBoardBuilder::getObject(){
    return gameboard;
}

void GameBoardBuilder::RefreshTiles(sf::Vector2f position, Resources resources){

    ChessBoard& board = gameboard.DrawableComponent.Board;
    auto TileDimensions = resources.spriteManager->AccessSprite("RegularTile1").getGlobalBounds().getSize(); //Used to work out how big the tile sprite is

    for (int i{0}; i < Constants::MAX_BOARD_DIMENSIONS.x; i++){
        for (int j{0}; j < Constants::MAX_BOARD_DIMENSIONS.y; j++){

            int index = 240 - j*16 + i;
            Tile t = board.GetGrid().TileList[index];
            sf::Vector2f tilePos = position + sf::Vector2f{i*TileDimensions.x, j*TileDimensions.y};
            bool ChequerBoardBool = (i%2 + j%2) %2;

            if (!t.isActive){
                
                if (ChequerBoardBool){
                    gameboard.DrawableComponent.Tiles[index] = resources.spriteManager->AccessSprite("InactiveTile2");
                } else {
                    gameboard.DrawableComponent.Tiles[index] = resources.spriteManager->AccessSprite("InactiveTile1");
                };

            } else {

                switch (t.type){
                
                    case (TileType::REGULAR):

                        if (ChequerBoardBool){
                            gameboard.DrawableComponent.Tiles[index] = resources.spriteManager->AccessSprite("RegularTile2");
                        } else {
                            gameboard.DrawableComponent.Tiles[index] = resources.spriteManager->AccessSprite("RegularTile1");
                        };

                }
            }

            MemSprite overlay;
            if (t.promoteBlack && t.promoteWhite){
                overlay = resources.spriteManager->AccessSprite("MixedPromotionOverlay");
            } else if (t.promoteWhite){
                overlay = resources.spriteManager->AccessSprite("WhitePromotionOverlay");
            } else if (t.promoteBlack){
                overlay = resources.spriteManager->AccessSprite("BlackPromotionOverlay");
            }
            overlay.setPosition(tilePos);
            gameboard.DrawableComponent.PromotionOverlay.push_back(overlay);

            gameboard.DrawableComponent.Tiles[index].setPosition(tilePos);

        };
    };

};





void GameBoardBuilder::RefreshPieces(Element<BoardComponent>& gameboard1, sf::Vector2f position, Resources resources){

    ChessBoard& board = gameboard1.DrawableComponent.Board;
    auto TileDimensions = resources.spriteManager->AccessSprite("RegularTile1").getGlobalBounds().getSize();

    for (int i{0}; i < Constants::MAX_BOARD_DIMENSIONS.x; i++){
        for (int j{0}; j < Constants::MAX_BOARD_DIMENSIONS.y; j++){

            int index = 240 - j*16 + i;
            const Piece& p = board.GetPieces()[board.GetGrid().PieceGrid[index]];
            sf::Vector2f piecePos = position + sf::Vector2f{i*TileDimensions.x, j*TileDimensions.y};

            MemSprite pieceSprite;
            auto name = p.information.name;
            auto team = p.Team;

            if (name == "Null"){
                pieceSprite = resources.spriteManager->AccessSprite(name);
            } else if (team == 0){
                pieceSprite = resources.spriteManager->AccessSprite("White_" + name);
            } else if (team == 1){
                pieceSprite = resources.spriteManager->AccessSprite("Black_" + name);
            }

            pieceSprite.setPosition(piecePos);
            gameboard1.DrawableComponent.Pieces[index] = pieceSprite;



        }
    }


};




GameBoardBuilder::GameBoardBuilder(ChessBoard board, sf::Vector2f position, Resources resources){

    auto TileDimensions = resources.spriteManager->AccessSprite("RegularTile1").getGlobalBounds().getSize();
    auto boardSize = sf::Vector2f(float(Constants::MAX_BOARD_DIMENSIONS.x), float(Constants::MAX_BOARD_DIMENSIONS.y));
    auto BoardDimensions = sf::Vector2f{TileDimensions.x * boardSize.x, TileDimensions.y * boardSize.y};
    auto boardRect = sf::FloatRect(position, BoardDimensions);
    
    //Set up Tiles
    gameboard.DrawableComponent.Board = board;
    gameboard.DrawableComponent.CurrentPieceOverlay = resources.spriteManager->AccessSprite("CurrentTileOverlay");
    RefreshTiles(position, resources);
    RefreshPieces(gameboard,position, resources);

    auto drawFunction = [](Element<BoardComponent>* element, Resources appResources){
        for (auto sprite : element->DrawableComponent.Tiles){
            appResources.globalTexture->draw(sprite); 
        };
        for (auto sprite : element->DrawableComponent.PromotionOverlay){
            appResources.globalTexture->draw(sprite); 
        };
        for (auto sprite : element->DrawableComponent.Pieces){
            appResources.globalTexture->draw(sprite); 
        };
        for (auto sprite : element->DrawableComponent.PossibleMoves){
            appResources.globalTexture->draw(sprite); 
        };

        appResources.globalTexture->draw(element->DrawableComponent.CurrentPieceOverlay);
    };

    StatePtr Standardstate = std::make_shared<State<Element<BoardComponent>>>();
    StatePtr Clickedstate = std::make_shared<State<Element<BoardComponent>>>();

    Standardstate->UpdateCallback = [Clickedstate, boardRect, TileDimensions, position](Element<BoardComponent>* element, Resources appResources) -> PotentialStatePtr{

        auto mousePos = sf::Vector2f(sf::Mouse::getPosition(*appResources.window));
        auto mousePosRelative = mousePos - position;
        int i = int(mousePosRelative.x/TileDimensions.x);
        int j = int(mousePosRelative.y/TileDimensions.y);

        auto event = appResources.eventList->MouseButtons.at("Left");

        if(event.Pressed && boardRect.contains(mousePos)){
            element->DrawableComponent.CurrentLocation = {i, j};
            return std::optional(Clickedstate);
        } else {
            return std::nullopt;
        };

    };

    Clickedstate->UpdateCallback = [Standardstate, TileDimensions, position, this](Element<BoardComponent>* element, Resources appResources) -> PotentialStatePtr{

        auto mousePos = sf::Vector2f(sf::Mouse::getPosition(*appResources.window));
        auto mousePosRelative = mousePos - position;
        int i = int(mousePosRelative.x/TileDimensions.x);
        int j = int(mousePosRelative.y/TileDimensions.y);
        sf::Vector2i loc = element->DrawableComponent.CurrentLocation;

        auto event = appResources.eventList->MouseButtons.at("Left");

        if(event.Pressed && i < 16 && j < 16 && loc != sf::Vector2i{i,j}){

            auto is_right_move = [i,j](Move m) { return m.to == (240 - j*16 + i); };
            
            auto index = std::find_if(element->DrawableComponent.currentMoves.begin(), element->DrawableComponent.currentMoves.end(), is_right_move);

            if (index != element->DrawableComponent.currentMoves.end()){

                element->DrawableComponent.Board.Play(*index);
                RefreshPieces(*element, position, appResources);
            } 

            return std::optional(Standardstate);

        } else {

            return std::nullopt;
        };

        return std::nullopt;

    };





    Standardstate->EnterCallback = [](Element<BoardComponent>* element){};
    Standardstate->ExitCallback = [](Element<BoardComponent>* element){};
    Standardstate->DrawCallback = drawFunction;

    Clickedstate->EnterCallback = [resources, position, TileDimensions](Element<BoardComponent>* element){

        //Draw the overlay for the grid square you selected
        sf::Vector2i loc = element->DrawableComponent.CurrentLocation;
        sf::Vector2f tilePos = position + sf::Vector2f{loc.x*TileDimensions.x, loc.y*TileDimensions.y};
        element->DrawableComponent.CurrentPieceOverlay.setPosition(tilePos);

        //Draw the moves available
        if(loc.x < 16 && loc.y < 16){

            int indexFrom = 240 - loc.y*16 + loc.x;
            const Piece& p = element->DrawableComponent.Board.GetPieces()[element->DrawableComponent.Board.GetGrid().PieceGrid[indexFrom]];

            auto Moves = element->DrawableComponent.Board.GenerateLegalMoves(p);

            for (auto move : Moves){
                MemSprite moveSprite = resources.spriteManager->AccessSprite("MoveOverlay");
                auto moveVector = IndexToVec(move.to);
                moveVector.y = 15-moveVector.y;
                moveSprite.setPosition(position + sf::Vector2f{moveVector.x*TileDimensions.x, moveVector.y*TileDimensions.y});
                element->DrawableComponent.PossibleMoves[move.to] = moveSprite;
            }

            element->DrawableComponent.currentMoves = Moves;

        }
    };

    MemSprite nullS = resources.spriteManager->AccessSprite("Null");
    Clickedstate->ExitCallback = [nullS](Element<BoardComponent>* element){ 
        for (auto& moveS : element->DrawableComponent.PossibleMoves){
            moveS = nullS;
        }
    };
    Clickedstate->DrawCallback = drawFunction;

    gameboard.StateStack = {};
    gameboard.StateStack.push(Standardstate);


}