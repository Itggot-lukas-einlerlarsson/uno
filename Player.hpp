#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Card.hpp"

class Player
{
private:
  const int SIZE = 20; //max size of hand.
  std::string name;
  int amountOfCards;
  Card* hand;
  Card passCard;


public:
  //constructors
  Player();
  Player(const std::string& name, const int& amount, Card cardsAtStart[]);

  //getters
  int get_amountOfCards();
  std::string get_name();
  Card* get_hand() const;

  //doers
  void addCard(const Card& card);//add card to hand
  void printHand() const; //print players hand

  //print cards and choose cards:
  Card handMenu(const Card& cmpCard);
  Card handMenu(const Card& cmpCard, const Card& card);

  //Destructors
  ~Player ();
};

#endif //PLAYER_HPP
