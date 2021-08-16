#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "../src/Card.cpp"
#include "../src/Player.cpp"


//Not using linked list.
class Board
{
private:
  const int SIZE = 108;
  const int HAND_SIZE = 20; //max size of hand
  int amountOfPlayers;
  int deckSize;


  Card* deck;
  std::vector<Card> usedDeck; //graveyard, playryard

  //Card topCard;

  Player** players;
  int playerIndex;
  int startAmount;
  int circulation; //if 1 -> going right in array, if -1 -> going left. in players array

public:
  //Constructor
  Board ();

  //Doers
  void shuffle(); //use in start after createDeck(); and after deck is out of cards. -> when decksize is 0
  void start(); //handle all nullptrs
  void play();
  bool checkUno();
  bool isViable(const Card& card);


  void createDeck();
  //bool playerDraw(); //checks if players hand is full, if not pick up card. else his turn.
  //void printPlayerCards();
  void rotate(); //depend on circulation and shifts via playerIndex
  //void clear(); // new game -> start(); or quit.
  void printDeck();
  void printPlayerCards();

  //Destructor
  ~Board ();
};

#endif //BOARD_HPP
