#include <gtest/gtest.h>
#include "../src/Chess/Board/Board.hpp"
#include "../src/Chess/Move/Move.hpp"
#include "../src/Resources/EventList.hpp"
#include "Resources/EventList.hpp"

// First test to make sure test suite works - Does some basic assertions on global constants.
TEST(ChessBoard, CheckDataTypeSizes) {
  // Expect equality.
  EXPECT_GE(8, sizeof(Piece));
  EXPECT_EQ(3, sizeof(Move));
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