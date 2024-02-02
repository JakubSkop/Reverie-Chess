#include "Board.hpp"

#include <iostream>
#include <string>
#include <math.h>
#include <utility>
#include <ranges>
#include <algorithm>

namespace views = std::ranges::views;

const GridofTiles& ChessBoard::GetGrid(){
    return Grid;
};

const std::array<Piece, std::numeric_limits<uint8_t>::max()>& ChessBoard::GetPieces(){
    return PieceList;
}

void ChessBoard::AddPiece(Piece p){
    uint8_t index = VecToIndex(p.Position);
    PieceList[last_piece_pointer] = p;
    Grid.PieceGrid[index] = last_piece_pointer;
    last_piece_pointer++;
};

void ChessBoard::SetTileMap(Tilemap m){
    Grid.TileList = m;
};

void ChessBoard::Print(printMode pm){
    for (int i{0}; i < 16; i++){
        std::cout << "\n";
        for (int j{0}; j < 16; j++){

            int n = 240-i*16+j;
            std::string msg;

            switch(pm){
                case printMode::TILES:{
                    Tile currentTile = Grid.TileList[n];
                    msg = std::to_string(static_cast<int>(currentTile.type)) + " ";
                    break;
                }

                case printMode::PIECE_INDICES:{
                    uint8_t currentPieceIndex = Grid.PieceGrid[n];
                    msg = std::to_string(static_cast<int>(currentPieceIndex)) + " ";
                    break;
                }

            };

            std::cout << msg;
        
        }
    }
};

//This method is useful later for determing whether a move is legal or not
//It assumes the board was in a legal state upto to this point
bool ChessBoard::CheckLegality(Move move){

    bool team = PieceList[Grid.PieceGrid[move.from]].Team;//piece.Team;

    Play(move);

    auto kingPosList = PieceList 
    |   views::filter([team](Piece& p){ return (p.Category == PieceCategory::King) && (p.Team == team); })
    |   views::transform([](Piece& p){ return VecToIndex(p.Position); });
    auto enemyTeamAttackPositions = PieceList 
    |   views::filter([team](Piece& p){ return (p.Team != team); })
    |   views::transform([this](Piece& p){ return GeneratePseudoLegalMoves_Capture(p);})
    |   views::join
    |   views::transform([](Move m){ return m.to;});

    bool doesEnemyAttackKing = (std::ranges::find_first_of(enemyTeamAttackPositions, kingPosList) != enemyTeamAttackPositions.end());
    
    Unplay(move);

    return !doesEnemyAttackKing;
};


//Method for executing a move on the board
void ChessBoard::Play(Move move){

    if (move.castle){

        Piece& king = PieceList[Grid.PieceGrid[move.from]];
        Piece& rook = PieceList[Grid.PieceGrid[move.to]];

        king.HasMoved = true;
        rook.HasMoved = true;

        int8_t dir = 2 * static_cast<int8_t>(move.from < move.to) - 1; //calculates the direction of castling

        //king.Position.x += 2*dir;
        //rook.Position.x = king.Position.x - dir;

        std::swap(Grid.PieceGrid[move.to], Grid.PieceGrid[move.from + dir]);
        std::swap(Grid.PieceGrid[move.from], Grid.PieceGrid[move.from + 2*dir]);

    } else {

        Piece& some_piece = PieceList[Grid.PieceGrid[move.from]];
        Piece& captured_piece = PieceList[Grid.PieceGrid[move.to]];

        some_piece.Position = IndexToVec(move.to);

        some_piece.HasMoved = true;
        captured_piece.Alive = false; 

        Grid.PieceGrid[move.to] = Grid.PieceGrid[move.from];
        Grid.PieceGrid[move.from] = 0;

    };

};

void ChessBoard::Unplay(Move move){ //input parameter represents last played move, which we want to undo

    if (move.castle){

        int8_t dir = 2 * static_cast<int8_t>(move.from > move.to) - 1; //calculates the direction of castling

        std::swap(Grid.PieceGrid[move.to], Grid.PieceGrid[move.from + dir]); //Moves the rook
        std::swap(Grid.PieceGrid[move.from], Grid.PieceGrid[move.from + 2*dir]); //Moves the king

        Piece& king = PieceList[Grid.PieceGrid[move.from]];
        Piece& rook = PieceList[Grid.PieceGrid[move.to]];

        king.HasMoved = false;
        rook.HasMoved = false;

    } else {

        Grid.PieceGrid[move.from] = Grid.PieceGrid[move.to];
        Grid.PieceGrid[move.to] = move.captureIndex;

        Piece& some_piece = PieceList[Grid.PieceGrid[move.from]];
        Piece& captured_piece = PieceList[Grid.PieceGrid[move.to]];
        some_piece.HasMoved = !move.firstMove;
        captured_piece.Alive = true; 

        some_piece.Position = IndexToVec(move.from);


    };

};



std::vector<Move> ChessBoard::GeneratePseudoLegalMoves_NonCapture(const Piece& piece){

    MoveBehaviour moveBehaviour;
    if (piece.HasMoved){
        moveBehaviour = piece.Behaviour.StandardMoveBehaviour;      
    } else {
        moveBehaviour = piece.Behaviour.FirstMoveBehaviour;    
    }; //Selects the right behaviour for the piece depending on whether it has moved yet or not

    std::vector<Move> moves{};
    bool team = piece.Team;

    //Deals with all the jumping moves for pieces - these are not affected by pieces or inactive tiles being in the way
    for(auto jumpMove: moveBehaviour.JumpMoves){

        if (team == 1){
            jumpMove *= int8_t{-1}; //Invert jumpmoves if team is black to account for opposite side moving in opposite direction
        }

        Move resultantMove; //Initialize variable for storing the resulting move
        sf::Vector2<int8_t> jumpVec = piece.Position + jumpMove; //Where the piece would land if it attempted this jumping move
        
        if (jumpVec.x >= 0 && jumpVec.y >= 0 && jumpVec.x < 16 && jumpVec.y < 16){ //check if jump was out of bound

            uint8_t currentPos = VecToIndex(piece.Position); //Index version of currentPosition as opposed to vector
            uint8_t jumpPos = VecToIndex(jumpVec);

            bool isJumpTileActive = Grid.TileList[jumpPos].isActive; //Check if the tile is active
            uint8_t JumpTilePiece = (Grid.PieceGrid[jumpPos]); //If is a piece at a square is a 0, then no piece is there
            bool isJumpTileEmpty = ! static_cast<bool>(JumpTilePiece);

            if (isJumpTileActive && isJumpTileEmpty){

                Tile jumpTile = Grid.TileList[jumpPos];
                bool isJumpTilePromoting; //Checks whether the piece would promote on the incoming tile

                if (team == 0){
                    isJumpTilePromoting = jumpTile.promoteWhite;
                } else {
                    isJumpTilePromoting = jumpTile.promoteBlack;
                };

                resultantMove = Move{currentPos, jumpPos, JumpTilePiece, isJumpTilePromoting, false, !piece.HasMoved};
                moves.emplace_back(resultantMove);

            }
        }
    }

    //Deals with all sliding moves - think analogous to how bishops and rooks moves, but some pieces may have finite distances for sliding
    //Loops over every direction to slide
    for(int i = 0; i < moveBehaviour.SlidingDistances.size(); i++){

        int8_t slideCounter = 1; //For incrementing until a piece can't slide any further
        int8_t slideDistance = moveBehaviour.SlidingDistances[i];

        //ugly hack -> generates vectors for all cardinal directions for sliding without any if statements
        sf::Vector2<int8_t> direction = {   static_cast<int8_t>(round(0.7*abs(4-(i+6)%8)-1.4))   ,   static_cast<int8_t>(round(abs(4-i)*0.7-1.4))   };
        //Basically generates these vectors: {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, etc

        if (team == 1){
            direction *= int8_t{-1}; //Invert direction if team is black to account for opposite side moving in opposite direction
        }

        sf::Vector2<int8_t> jumpMove = direction * slideCounter;
        sf::Vector2<int8_t> jumpVec = piece.Position + jumpMove;
        Move resultantMove; //Initialize variable for storing the resulting move

        while(jumpVec.x >= 0 && jumpVec.y >= 0 && jumpVec.x < 16 && jumpVec.y < 16 && (slideCounter <= slideDistance)){

            uint8_t currentPos = VecToIndex(piece.Position); //Index version of currentPosition as opposed to vector
            uint8_t jumpPos = VecToIndex(jumpVec); //Similar idea to above

            bool isJumpTileActive = Grid.TileList[jumpPos].isActive; //Whether that tile can even be stepped on

            if (isJumpTileActive){

                uint8_t JumpTilePiece = (Grid.PieceGrid[jumpPos]); //If is a piece at a square is a 0, then no piece is there
                bool isJumpTileEmpty = ! static_cast<bool>(JumpTilePiece);

                Tile jumpTile = Grid.TileList[jumpPos];
                bool isJumpTilePromoting; //Checks whether the piece would promote on the incoming tile

                if (team == 0){
                    isJumpTilePromoting = jumpTile.promoteWhite;
                } else {
                    isJumpTilePromoting = jumpTile.promoteBlack;
                };

                if (isJumpTileEmpty){

                    resultantMove = Move{currentPos, jumpPos, JumpTilePiece, isJumpTilePromoting, false, !piece.HasMoved};
                    moves.emplace_back(resultantMove);

                } else {

                    break;

                };

            } else {

                break;

            };

            slideCounter++;
            jumpMove = direction * slideCounter;
            jumpVec = piece.Position + jumpMove;

        }
    };


    //Now Deal with castling - a move exclusive to kingType pieces
    if (piece.Category == PieceCategory::King && !piece.HasMoved){
        
        for (auto direction: {sf::Vector2<int8_t>{-1,0}, sf::Vector2<int8_t>{1,0}}){

            int8_t slideCounter = 1;
            sf::Vector2<int8_t> jumpMove = direction * slideCounter;
            sf::Vector2<int8_t> jumpVec = piece.Position + jumpMove;
            uint8_t currentPos = VecToIndex(piece.Position);
            uint8_t jumpPos = VecToIndex(jumpVec); 

            while (jumpVec.x >= 0 && jumpVec.y >= 0 && jumpVec.x < 16 && jumpVec.y < 16){

                bool isJumpTileActive = Grid.TileList[jumpPos].isActive;

                if (isJumpTileActive){

                    bool isJumpTileTaken = static_cast<bool>(Grid.PieceGrid[jumpPos]); //If is a piece at a square is a 0, then no piece is there
                    bool isJumpTileContainingRook = (PieceList[Grid.PieceGrid[jumpPos]].Category == PieceCategory::Rook);
                    bool isJumpTilePieceSameColour = (PieceList[Grid.PieceGrid[jumpPos]].Team == team);

                    if (isJumpTileTaken){

                        if (isJumpTileContainingRook && isJumpTilePieceSameColour){

                            auto resultantMove = Move{currentPos, jumpPos, 0, false, true, true};
                            moves.emplace_back(resultantMove);

                        } 

                        break;

                    };

                } else {

                    break;
                }

                slideCounter++;
                jumpMove = direction * slideCounter;
                jumpVec = piece.Position + jumpMove;
                jumpPos = VecToIndex(jumpVec); 

            };

        };

    };

    //Return all of these pseudolegal moves
    return moves;
};







std::vector<Move> ChessBoard::GeneratePseudoLegalMoves_Capture(const Piece& piece){

    MoveBehaviour attackBehaviour;
    if (piece.HasMoved){ 
        attackBehaviour = piece.Behaviour.StandardAttackBehaviour;    
    } else {   
        attackBehaviour = piece.Behaviour.FirstAttackBehaviour; 
    }; //Selects the right behaviour for the piece depending on whether it has moved yet or not

    std::vector<Move> moves{};
    bool team = piece.Team;

    //Deals with all the jumping attacks for pieces - these are not affected by pieces or inactive tiles being in the way
    for(auto jumpAttack: attackBehaviour.JumpMoves){

        if (team == 1){
            jumpAttack *= int8_t{-1}; //Invert jumpAttacks if team is black to account for opposite side moving in opposite direction
        };

        Move resultantMove; //Initialize variable for storing the resulting move
        sf::Vector2<int8_t> jumpVec = piece.Position + jumpAttack; //Where the piece would land if it attempted this jumping attack
        
        if (jumpVec.x >= 0 && jumpVec.y >= 0 && jumpVec.x < 16 && jumpVec.y < 16){ //check if jump was out of bound

            uint8_t currentPos = VecToIndex(piece.Position); //Index version of currentPosition as opposed to vector
            uint8_t jumpPos = VecToIndex(jumpVec);

            bool isJumpTileActive = Grid.TileList[jumpPos].isActive; //Check if the tile is active
            uint8_t JumpTilePiece = (Grid.PieceGrid[jumpPos]); //If is a piece at a square is a 0, then no piece is there
            bool isJumpTileOccupied = static_cast<bool>(JumpTilePiece);
            bool isJumpTilePieceDifferentColours = (PieceList[Grid.PieceGrid[jumpPos]].Team != team);

            if (isJumpTileActive && isJumpTileOccupied && isJumpTilePieceDifferentColours){

                Tile jumpTile = Grid.TileList[jumpPos];
                bool isJumpTilePromoting; //Checks whether the piece would promote on the incoming tile
                
                if (team == 0){
                    isJumpTilePromoting = jumpTile.promoteWhite;
                } else {
                    isJumpTilePromoting = jumpTile.promoteBlack;
                };

                resultantMove = Move{currentPos, jumpPos, JumpTilePiece, isJumpTilePromoting, false, !piece.HasMoved};
                moves.emplace_back(resultantMove);

            }
        }
    }


    //Deals with all sliding attacks
    //Loops over every direction to slide
    for(int i = 0; i < attackBehaviour.SlidingDistances.size(); i++){

        int8_t slideCounter = 1; //For incrementing until a piece can't slide any further
        int8_t slideDistance = attackBehaviour.SlidingDistances[i];

        //ugly hack -> generates vectors for all cardinal directions for sliding without any if statements
        sf::Vector2<int8_t> direction = {   static_cast<int8_t>(round(0.7*abs(4-(i+6)%8)-1.4))   ,   static_cast<int8_t>(round(abs(4-i)*0.7-1.4))   };
        //Basically generates these vectors: {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, etc

        if (team == 1){
            direction *= int8_t{-1}; //Invert direction if team is black to account for opposite side moving in opposite direction
        }

        sf::Vector2<int8_t> jumpAttack = direction * slideCounter;
        sf::Vector2<int8_t> jumpVec = piece.Position + jumpAttack;
        Move resultantMove; //Initialize variable for storing the resulting move

        while(jumpVec.x >= 0 && jumpVec.y >= 0 && jumpVec.x < 16 && jumpVec.y < 16 && (slideCounter <= slideDistance)){

            uint8_t currentPos = VecToIndex(piece.Position); //Index version of currentPosition as opposed to vector
            uint8_t jumpPos = VecToIndex(jumpVec); //Similar idea to above

            bool isJumpTileActive = Grid.TileList[jumpPos].isActive; //Whether that tile can even be stepped on

            if (isJumpTileActive){

                uint8_t JumpTilePiece = (Grid.PieceGrid[jumpPos]); //If is a piece at a square is a 0, then no piece is there
                bool isJumpTileOccupied = static_cast<bool>(JumpTilePiece);

                Tile jumpTile = Grid.TileList[jumpPos];
                bool isJumpTilePromoting; //Checks whether the piece would promote on the incoming tile
                
                if (team == 0){
                    isJumpTilePromoting = jumpTile.promoteWhite;
                } else {
                    isJumpTilePromoting = jumpTile.promoteBlack;
                };

                if (isJumpTileOccupied){

                    bool isJumpTilePieceDifferentColours = (PieceList[Grid.PieceGrid[jumpPos]].Team != team);

                    if (isJumpTilePieceDifferentColours){

                        resultantMove = Move{currentPos, jumpPos, JumpTilePiece, isJumpTilePromoting, false, !piece.HasMoved};
                        moves.emplace_back(resultantMove);

                    } 

                    break;

                };

            } else {

                break;

            };

            slideCounter++;
            jumpAttack = direction * slideCounter;
            jumpVec = piece.Position + jumpAttack;

        }
    };


    //Return all of these pseudolegal attacks
    return moves;
};



std::vector<Move> ChessBoard::GenerateLegalMoves(const Piece& piece){
    auto pseudomoves = GeneratePseudoLegalMoves_NonCapture(piece);
    auto pseudoattacks = GeneratePseudoLegalMoves_Capture(piece);
    std::vector<Move> legal_moves;

    std::copy_if(pseudomoves.begin(), pseudomoves.end(), std::back_inserter(legal_moves), [this](Move m){return CheckLegality(m);});
    std::copy_if(pseudoattacks.begin(), pseudoattacks.end(), std::back_inserter(legal_moves), [this](Move m){return CheckLegality(m);});

    return legal_moves;
};

std::vector<Move> ChessBoard::GenerateAllMoves(bool colour){
    std::vector<Move> all_moves;
    for (int i{1}; i < last_piece_pointer; i++){
        Piece p = PieceList[i];
        if (p.Alive && p.Team == colour){
            auto m = GenerateLegalMoves(p);
            all_moves.insert(all_moves.end(), m.begin(), m.end());
        }
    }
    return all_moves;

};

std::vector<Move> ChessBoard::GenerateAllMoves(){
    std::vector<Move> all_moves;
    for (int i{1}; i < last_piece_pointer; i++){
        Piece p = PieceList[i];
        if (p.Alive){
            auto m = GenerateLegalMoves(p);
            all_moves.insert(all_moves.end(), m.begin(), m.end());
        }
    }
    return all_moves;

};

ChessBoard Board_for_Level_N(int levelnum){
    ChessBoard board = ChessBoard();
    
    switch (levelnum){

        case (1):
            board.SetTileMap(PresetTileMaps::Regular);
            board.AddPiece(Pieces::PawnFactory({4,5}, false));
            board.AddPiece(Pieces::PawnFactory({5,5}, false));
            board.AddPiece(Pieces::PawnFactory({6,5}, false));
            board.AddPiece(Pieces::PawnFactory({7,5}, false));
            board.AddPiece(Pieces::PawnFactory({8,5}, false));
            board.AddPiece(Pieces::PawnFactory({9,5}, false));
            board.AddPiece(Pieces::PawnFactory({10,5}, false));
            board.AddPiece(Pieces::PawnFactory({11,5}, false));

            board.AddPiece(Pieces::PawnFactory({4,10}, true));
            board.AddPiece(Pieces::PawnFactory({5,10}, true));
            board.AddPiece(Pieces::PawnFactory({6,10}, true));
            board.AddPiece(Pieces::PawnFactory({7,10}, true));
            board.AddPiece(Pieces::PawnFactory({8,10}, true));
            board.AddPiece(Pieces::PawnFactory({9,10}, true));
            board.AddPiece(Pieces::PawnFactory({10,10}, true));
            board.AddPiece(Pieces::PawnFactory({11,10}, true));

            board.AddPiece(Pieces::KnightFactory({5,4}, false));
            board.AddPiece(Pieces::KnightFactory({10,4}, false));

            board.AddPiece(Pieces::KnightFactory({5,11}, true));
            board.AddPiece(Pieces::KnightFactory({10,11}, true));

            board.AddPiece(Pieces::BishopFactory({6,4}, false));
            board.AddPiece(Pieces::BishopFactory({9,4}, false));

            board.AddPiece(Pieces::BishopFactory({6,11}, true));
            board.AddPiece(Pieces::BishopFactory({9,11}, true));

            board.AddPiece(Pieces::RookFactory({4,4}, false));
            board.AddPiece(Pieces::RookFactory({11,4}, false));

            board.AddPiece(Pieces::RookFactory({4,11}, true));
            board.AddPiece(Pieces::RookFactory({11,11}, true));

            board.AddPiece(Pieces::QueenFactory({7,4}, false));

            board.AddPiece(Pieces::QueenFactory({7,11}, true));

            board.AddPiece(Pieces::KingFactory({8,4}, false));

            board.AddPiece(Pieces::KingFactory({8,11}, true));

            break;
        default:
            board.SetTileMap(PresetTileMaps::Basic);
            break;

    };

    return board;

}