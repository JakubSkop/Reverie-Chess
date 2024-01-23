#include <gtest/gtest.h>
#include "../src/Chess/Board/Board.hpp"
#include "../src/Chess/Move/Move.hpp"
#include "../src/Resources/EventList.hpp"
#include "Resources/EventList.hpp"

// First test to make sure test suite works - Does some basic assertions on global constants.
TEST(ChessBoard, CheckDataTypeSizes) {
  // Expect equality.
  EXPECT_GE(144, sizeof(Piece));
  EXPECT_EQ(5, sizeof(Move));
}


TEST(ChessBoard, PseudoLegalMoves_Test) {
  // Expect equality.

  ChessBoard board = ChessBoard();
  Piece pawn1 = Pieces::PawnFactory({0,0}, true);
  board.AddPiece(pawn1, 0);

  auto res = board.GeneratePseudoLegalMoves(pawn1);

  for (auto i: res){
    std::cout << i;
  }

}











TEST(EventLists, CheckEventFetching) {
  EventList List;

  Event::MouseButtonEvent mouse1;
  mouse1.button = Mouse::Right;

  Event Emouse1{Event::EventType::MouseButtonReleased};
  Emouse1.mouseButton = mouse1;

  List.addEvent(Emouse1);
  EXPECT_EQ(List.MouseButtons["Right"].Released, true);
  EXPECT_EQ(List.MouseButtons["Left"].Released, false);

}