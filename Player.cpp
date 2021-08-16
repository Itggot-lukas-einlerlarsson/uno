#include "../include/Player.hpp"

//constructors
Player::Player ()
: name("Default"), amountOfCards(0), hand(new Card[SIZE])
{
  passCard.function = "PASS";
  passCard.color = "BLACK";
}

Player::Player(const std::string& name, const int& amount, Card cardsAtStart[])
: name(name), amountOfCards(amount), hand(new Card[SIZE])
{
  for (size_t i = 0; i < amountOfCards; i++)
  {
    hand[i] = cardsAtStart[i];
  }
  passCard.function = "PASS";
  passCard.color = "BLACK";
}


//getters
int Player::get_amountOfCards()
{
  return amountOfCards;
}
std::string Player::get_name()
{
  return name;
}
Card* Player::get_hand() const
{
  return hand;
}


//doers
//add card to hand
void Player::addCard(const Card& card)
{
  if (amountOfCards < SIZE)
  {
    hand[amountOfCards] = card;
    amountOfCards++;
  }
}

void Player::printHand() const
{
  std::cout << name << " cards: " <<'\n';
  //std::cout << std::setw(40) << '\n';
  for (size_t i = 0; i < amountOfCards; i++)
  {
    //std::cout << "Card nr " << i << "\tNumber: " << hand[i].number <<"\tColor: " << hand[i].color << "\tFunction: "  << hand[i].function << '\n';
    if (i > amountOfCards-3)
    {
      std::cout << "Card nr " << i << '\n';
      std::cout << "_________________________" << '\n';
      std::cout << "|" << "\t" << "\t" << "\t" << "|" <<'\n'
                << "|" << "\t" << hand[i].color << "\t\t" << "|" <<'\n'
                << "|" << "\t" << hand[i].function << "\t\t" << "|" <<'\n'
                << "|" << "\t" << hand[i].number << "\t\t" << "|" <<'\n';
      std::cout << "|_______________________|" << '\n';
      std::cout << '\n';
    }
    else
    {
      std::cout << "Card nr " << i << "\t\t\t" << "Card nr " << i+1 << '\n';
      std::cout << "_________________________" <<'\t' << "_________________________" << '\n';
      std::cout << "|" << "\t" << "\t" << "\t" << "|" <<'\t' << "|" << "\t" << "\t" << "\t" << "|" << '\n'
                << "|" << "\t" << hand[i].color << "\t\t" << "|" <<'\t' << "|" << "\t" << hand[i+1].color << "\t\t" << "|" << '\n'
                << "|" << "\t" << hand[i].function << "\t\t" << "|" <<'\t' <<  "|" << "\t" << hand[i+1].function << "\t\t" << "|" << '\n'
                << "|" << "\t " << hand[i].number << "\t\t" << "|" <<'\t' << "|" << "\t  " << hand[i+1].number << "\t\t" << "|" << '\n';
      std::cout << "|_______________________|" <<'\t' << "|_______________________|" ;
      std::cout << '\n';
      i++;
    }
  }
  std::cout << '\n';
}


//print cards and choose cards:
Card Player::handMenu(const Card& cmpCard)
{
  //for (size_t i = 0; i < amountOfCards; i++)
  //{
  //  std::cout << "Card nr " << i << "Number: " << hand[i].number <<"Color: " << hand[i].color << "\tFunction: "  << hand[i].function << '\n';
  //}
  //std::cout << "\nCard on top: " << "\tNumber: " << cmpCard.number <<"\tColor: " << cmpCard.color << "\tFunction: "  << cmpCard.function << '\n';
  std::cout << "_________________________" << '\n';
  std::cout << "|" << "\t" << "\t" << "\t" << "|" <<'\n'
            << "|" << "\t" << cmpCard.color << "\t\t" << "|" <<'\n'
            << "|" << "\t" << cmpCard.function << "\t\t" << "|" <<'\n'
            << "|" << "\t" << cmpCard.number << "\t\t" << "|" <<'\n';
  std::cout << "|_______________________|" << '\n';
  std::cout << '\n';
  int choice;
  std::cout << "\n" << name << "s turn! your cards:" << '\n';
  printHand();
  std::cout << "What card do ya want to choose?" << ' ';
  std::cout << "To pass and add two cards in your hand, write -1" << '\n';
  std::cout << "Your choice: " << ' ';
  std::cin >> choice; //ev check if choice is valid.
  while (std::cin.fail() || (choice < -1 || choice > amountOfCards))
  {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cout << "Error: Enter only numbers and interval of cards" << '\n';
      std::cout << "Your choice: " << ' ';
      std::cin >> choice;
  }
  std::cin.ignore();
  if (choice == -1)
  {
    return passCard;
  }
  Card chosenCard = hand[choice];
  while (choice < amountOfCards-1) //move on up choice to erase the chosenCard
  {
    hand[choice] = hand[choice+1];
    choice++;
  }
  amountOfCards--; //kortet ska tas bort och allting ska flyttas nedåt.
  return chosenCard;
}

Card Player::handMenu(const Card& cmpCard, const Card& card)
{
  std::cout << "Unvalid card! choose again!" << '\n';
  addCard(card);
  std::cout << "_________________________" << '\n';
  std::cout << "|" << "\t" << "\t" << "\t" << "|" <<'\n'
            << "|" << "\t" << cmpCard.color << "\t\t" << "|" <<'\n'
            << "|" << "\t" << cmpCard.function << "\t\t" << "|" <<'\n'
            << "|" << "\t" << cmpCard.number << "\t\t" << "|" <<'\n';
  std::cout << "|_______________________|" << '\n';
  std::cout << '\n';
  int choice;
  std::cout << "\n" <<name << "s turn! your cards:" << '\n';
  printHand();
  std::cout << "What card do ya want to choose?" << ' ';
  std::cout << "To pass and add two cards in your hand, write -1" << '\n';
  std::cout << "Your choice: " << ' ';
  std::cin >> choice; //ev check if choice is valid.
  while (std::cin.fail() || (choice < -1 || choice > amountOfCards))
  {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cout << "Error: Enter only numbers and interval of cards" << '\n';
      std::cout << "Your choice: " << ' ';
      std::cin >> choice;
  }
  std::cin.ignore();
  if (choice == -1)
  {
    return passCard;
  }
  Card chosenCard = hand[choice];
  while (choice < amountOfCards-1) //move on up choice to erase the chosenCard
  {
    hand[choice] = hand[choice+1];
    choice++;
  }
  amountOfCards--; //kortet ska tas bort och allting ska flyttas nedåt.
  return chosenCard;
}


//Destructors
Player::~Player ()
{
  if (hand != nullptr)
  {
    delete [] hand;
  }
}
