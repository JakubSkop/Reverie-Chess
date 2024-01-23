#include "Game/App.hpp"
#include <iostream>

#include "src/Chess/Board/Board.hpp"

int main()
{

    //ChessBoard board = ChessBoard();
    //board.SetTileMap(PresetTileMaps::Basic);

    //Piece pawn1 = Pieces::PawnFactory({4,4}, false);
    //Piece bish = Pieces::BishopFactory({3,3}, true);
    //board.AddPiece(pawn1);
    //board.AddPiece(bish);

    //auto res = board.GenerateAllMoves();

    //for (auto i: res){
    //    std::cout << i << "\n";
    //}

    //board.Print(printMode::PIECE_INDICES);
    //board.Play(res[4]);
    //board.Print(printMode::PIECE_INDICES);

    Application App;
    App.Setup();
    App.GameLoop();

    return 0;
}