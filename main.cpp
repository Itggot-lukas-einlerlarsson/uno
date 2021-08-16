#include "include/Board.hpp"
#include "src/Board.cpp"


/*
  TODO: when deck only has 5 cards left, copy those and make them go to the top after you have put useddeck into deck and shuffled.?
  of just useddeck-> deck -> shuffle is also sufficient

  the last card cannot be a black card or function card. fix!

  Bättre grafik för korten när de visas för spelarna, fixa med iomanip och iostream +-

  den verkar gå till uno ibland även om en spelare har flera kort kvar kek. får kolla över det också.

  isViable doesnt work. ?
*/

int main(int argc, char const *argv[])
{
  Board test;
  //test.createDeck();
  //test.printDeck();
  //test.shuffle();
  //test.printDeck();
  test.start();
  test.printDeck();
  test.printPlayerCards();
  test.play();
  //let each player take turns. See if the cards they play are viable. Check color, check number, check function.

  return 0;
}
