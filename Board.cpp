#include "../include/Board.hpp"

//Constructor
Board::Board ()
: amountOfPlayers(0), deckSize(0), deck(new Card[SIZE]),  players(nullptr), playerIndex(0), startAmount(3), circulation(1)
{
  //srand (time(NULL)); //player starts at 0 for now.
  //playerIndex = rand() & amountOfPlayers-1;
}

//Doers
//shuffle algoritm pog
void Board::shuffle()
{
  /* initialize random seed: */
  srand (time(NULL));

  int j; //holds randomnumber
  int i = deckSize-1;
  Card temp;

  while (i > 0)
  {
    j = rand() % i;
    if (j != i)
    {
      temp = deck[j];
      deck[j] = deck[i];
      deck[i] = temp;
    }
    i--;
  }
}

void Board::start() //handle all nullptrs
{
  std::cout << "Welcome to UNO!" << '\n';
  std::cout << std::setw(20) <<"Right, how many players are you?\nMax 10, at least 2: " << ' ';
  std::cin >> amountOfPlayers;
  while (std::cin.fail())
  {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cout << "Error: Enter only numbers" << '\n';
      std::cout << "Your choice: " << ' ';
      std::cin >> amountOfPlayers;
  }
  std::cin.ignore();
  //Create deck -> send in all cards.
  this->createDeck(); //done
  std::cout << "createDeck done" << '\n';
  shuffle(); //alright
  std::cout << "shuffle done" << '\n';
  players = new Player*[amountOfPlayers];
  std::cout << "Players array created" << '\n';
  int index;
  Card* temp;
  std::string playerName;
  while (playerIndex < amountOfPlayers)
  {
    playerName = "Player nr ";
    temp = new Card[startAmount];
    index = 0;
    while(index < startAmount)
    {
      temp[index] = deck[deckSize-1];
      index++;
      deckSize--;
    }
    playerName += std::to_string(playerIndex);
    players[playerIndex] = new Player(playerName, startAmount, temp);
    playerIndex++;
    delete [] temp;
  }
  usedDeck.push_back(deck[deckSize-1]); //ad first card to useddeck to play with.
  deckSize--;
  std::cout << "players done" << '\n';
  std::cout << "players got cards" << '\n';
}

void Board::play()
{
  Card currCard;
  //srand (time(NULL)); //player starts at 0 for now.
  playerIndex = rand() & amountOfPlayers-1;
  //playerIndex = 2;
  Card* playedCard = &currCard;
  //player plays, display his menu, show deck.
  //rotate();
  while (checkUno() == false)
  {
    //if deck has only ten cards left... -> useddeck keep first card, and send rest to deck. then shuffle() deck.
    if (deckSize < 10)
    {
      //topCard = usedDeck[0]; ev, int nödvändigt. tar inte mycket plats ändå.
      for (size_t i = 1; i < usedDeck.size(); i++)
      {
        deck[deckSize] = usedDeck[i];
      }
      shuffle(); //i guess, vet inte om detta fungerar.
      //usedDeck.clear();
    }
    //send in card deck[deckSize]
    currCard = players[playerIndex]->handMenu(usedDeck[0]);
    //check in usedDeck if card is fine then
    while (isViable(*playedCard) == false)
    {
      currCard = players[playerIndex]->handMenu(usedDeck[0], *playedCard); //put card back in players hand and redo choice. perhaps add card.
    }
    if (playedCard->function == "PASS")
    {
      //gör en funktion för alla dess addcards där man bara slänger in ett index , ev
      players[playerIndex]->addCard(deck[deckSize-1]);
      deckSize--;
      players[playerIndex]->addCard(deck[deckSize-1]);
      deckSize--;
      rotate();
      continue;
    }
    if (playedCard->function == "REVERSE")
    {
      if (circulation == 1)
      {
        circulation = -1;
      }
      else
      {
        circulation = 1;
      }
    }
    if (playedCard->function == "+2")
    {
      if (circulation == 1)
      {
        if (playerIndex == amountOfPlayers-1)
        {
          players[0]->addCard(deck[deckSize-1]);
          deckSize--;
          players[0]->addCard(deck[deckSize-1]);
          deckSize--;
        }
        else
        {
          players[playerIndex+1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[playerIndex+1]->addCard(deck[deckSize-1]);
          deckSize--;
        }
      }
      else
      {
        if (playerIndex == 0)
        {
          players[amountOfPlayers-1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[amountOfPlayers-1]->addCard(deck[deckSize-1]);
          deckSize--;
        }
        else
        {
          players[playerIndex-1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[playerIndex-1]->addCard(deck[deckSize-1]);
          deckSize--;
        }
      }
    }
    if (playedCard->function == "+4")
    {
      if (circulation == 1)
      {
        if (playerIndex == amountOfPlayers-1)
        {
          players[0]->addCard(deck[deckSize-1]);
          deckSize--;
          players[0]->addCard(deck[deckSize-1]);
          deckSize--;
          players[0]->addCard(deck[deckSize-1]);
          deckSize--;
          players[0]->addCard(deck[deckSize-1]);
          deckSize--;
        }
        else
        {
          players[playerIndex+1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[playerIndex+1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[playerIndex+1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[playerIndex+1]->addCard(deck[deckSize-1]);
          deckSize--;
        }
      }
      else
      {
        if (playerIndex == 0)
        {
          players[amountOfPlayers-1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[amountOfPlayers-1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[amountOfPlayers-1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[amountOfPlayers-1]->addCard(deck[deckSize-1]);
          deckSize--;
        }
        else
        {
          players[playerIndex-1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[playerIndex-1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[playerIndex-1]->addCard(deck[deckSize-1]);
          deckSize--;
          players[playerIndex-1]->addCard(deck[deckSize-1]);
          deckSize--;
        }
      }
      std::string choice;
      std::cout << "What color do ya want to choose?" << '\n';
      std::cout << "Either 'RED', 'YELLOW', 'GREEN' or 'BLUE'" << '\n';
      std::cin >> choice;
      while (choice.compare("RED") != 0 && choice.compare("YELLOW") != 0 && choice.compare("GREEN") != 0 && choice.compare("BLUE") != 0)
      {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Either 'RED', 'YELLOW', 'GREEN' or 'BLUE'" << ' ';
        std::cin >> choice;
      }
      std::cin.ignore();
      playedCard->color = choice;
    }
    if (playedCard->function == "CHOOSE")
    {
      std::string choice;
      std::cout << "What color do ya want to choose?" << '\n';
      std::cout << "Either 'RED', 'YELLOW', 'GREEN' or 'BLUE'" << ' ';
      std::cin >> choice;
      while (choice.compare("RED") != 0 && choice.compare("YELLOW") != 0 && choice.compare("GREEN") != 0 && choice.compare("BLUE") != 0)
      {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Either 'RED', 'YELLOW', 'GREEN' or 'BLUE'" << ' ';
        std::cin >> choice;
      }
      std::cin.ignore();
      //if choice !någon av färgerna kör om...
      playedCard->color = choice;
    }
    if (playedCard->function == "SKIP")
    {
      rotate();
    }
    usedDeck.insert(usedDeck.begin(), *playedCard);
    rotate();
    //player plays, display his menu, show deck.
    //rotate();
  }
  std::cout << "UNO!" << '\n';
}

void Board::rotate()
{
  if (circulation == 1)
  {
    playerIndex++;
    if (playerIndex == amountOfPlayers)
    {
      playerIndex = 0;
    }
  }
  else
  {
    playerIndex--;
    if (playerIndex < 0)
    {
      playerIndex = amountOfPlayers-1;
    }
  }
}

bool Board::checkUno()
{
  bool uno = false;
  for (size_t i = 0; i < amountOfPlayers; i++)
  {
    if (players[i]->get_amountOfCards() == 0)
    {
      uno = true;
    }
  }
  return uno;
}

bool Board::isViable(const Card& card)
{
  bool isViable = true;
  if (card.color == "BLACK") //if it is the last card then it is not viable! ev
  {
    return isViable;
  }
  if (card.function != "NONE" && card.function == usedDeck[0].function)
  {
    return isViable;
  }
  if (card.number != -1 && card.number == usedDeck[0].number)
  {
    return isViable;
  }
  if (card.color == usedDeck[0].color || usedDeck[0].color == "BLACK")
  {
    return isViable;
  }
  isViable = false;
  return isViable;
}


void Board::createDeck()
{
  std::cout << "Createdeck!" << '\n';
  //each color consists of: one 0 card, two 1 cards, two 2s, 3s, 4s, 5s, 6s, 7s, 8s and 9s
  //each color consists of: two Draw Two cards; two Skip cards; and two Reverse cards
  if (deck != nullptr)
  {
    delete [] deck;
    deck = new Card[SIZE];
  }

  if (deck == nullptr)
  {
    deck = new Card[SIZE];
  }

  //index helper
  int i = 1;

  std::cout << "Red" << '\n';
  //first RED
  deck[deckSize] = Card(0, "RED");
  deckSize++;
  while (i < 10)
  {
    deck[deckSize] = Card(i, "RED");
    deck[deckSize+1] = Card(i, "RED");
    deckSize += 2;
    i++;
  }

  //two of each function
  deck[deckSize] = Card("SKIP", "RED");
  deck[deckSize+1] = Card("SKIP", "RED");
  deckSize += 2;

  deck[deckSize] = Card("REVERSE", "RED");
  deck[deckSize+1] = Card("REVERSE", "RED");
  deckSize += 2;

  deck[deckSize] = Card("+2", "RED");
  deck[deckSize+1] = Card("+2", "RED");
  deckSize += 2;


  std::cout << "Green" << '\n';
  //second GREEN
  i = 1;
  deck[deckSize] = Card(0, "GREEN");
  deckSize++;
  while (i < 10)
  {
    deck[deckSize] = Card(i, "GREEN");
    deck[deckSize+1] = Card(i, "GREEN");
    deckSize += 2;
    i++;
  }

  //two of each function
  deck[deckSize] = Card("SKIP", "GREEN");
  deck[deckSize+1] = Card("SKIP", "GREEN");
  deckSize += 2;

  deck[deckSize] = Card("REVERSE", "GREEN");
  deck[deckSize+1] = Card("REVERSE", "GREEN");
  deckSize += 2;

  deck[deckSize] = Card("+2", "GREEN");
  deck[deckSize+1] = Card("+2", "GREEN");
  deckSize += 2;


  //third YELLOW
  std::cout << "Yellow" << '\n';
  i = 1;
  deck[deckSize] = Card(0, "YELLOW");
  deckSize++;

  while (i < 10)
  {
    deck[deckSize] = Card(i, "YELLOW");
    deck[deckSize+1] = Card(i, "YELLOW");
    deckSize += 2;
    i++;
  }

  //two of each function
  deck[deckSize] = Card("SKIP", "YELLOW");
  deck[deckSize+1] = Card("SKIP", "YELLOW");
  deckSize += 2;

  deck[deckSize] = Card("REVERSE", "YELLOW");
  deck[deckSize+1] = Card("REVERSE", "YELLOW");
  deckSize += 2;

  deck[deckSize] = Card("+2", "YELLOW");
  deck[deckSize+1] = Card("+2", "YELLOW");
  deckSize += 2;


  std::cout << "Blue" << '\n';
  //fourth BLUE
  i = 1;
  deck[deckSize] = Card(0, "BLUE");
  deckSize++;

  while (i < 10)
  {
    deck[deckSize] = Card(i, "BLUE");
    deck[deckSize+1] = Card(i, "BLUE");
    deckSize += 2;
    i++;
  }

  //two of each function
  deck[deckSize] = Card("SKIP", "BLUE");
  deck[deckSize+1] = Card("SKIP", "BLUE");
  deckSize += 2;

  deck[deckSize] = Card("REVERSE", "BLUE");
  deck[deckSize+1] = Card("REVERSE", "BLUE");
  deckSize += 2;

  deck[deckSize] = Card("+2", "BLUE");
  deck[deckSize+1] = Card("+2", "BLUE");
  deckSize += 2;


  //fith BLACK -- wildcards //four of each
  i = 0;
  while (i < 4)
  {
    deck[deckSize] = Card("CHOOSE", "BLACK");
    deckSize++;
    i++;
  }
  i = 0;
  while (i < 4)
  {
    deck[deckSize] = Card("+4", "BLACK");
    deckSize++;
    i++;
  }
}


//bool playerDraw(); //checks if players hand is full, if not pick up card. else his turn.

//void clear(); // new game -> start(); or quit.

void Board::printDeck()
{
  if (deckSize == 0)
  {
    std::cout << "No cards in deck." << '\n';
    return;
  }
  for (size_t i = 0; i < deckSize; i++)
  {
    if (i == 0)
    {
      std::cout << "\nRED" << '\n';
    }
    if (i == 25)
    {
      std::cout << "\nGREEN" << '\n';
    }
    if (i == 50)
    {
      std::cout << "\nYELLOW" << '\n';
    }
    if (i == 75)
    {
      std::cout << "\nBLUE" << '\n';
    }
    if (i == 100)
    {
      std::cout << "\nBLACK" << '\n';
    }
    std::cout << deck[i].number << '\t';
  }
  std::cout << '\n';
}

void Board::printPlayerCards()
{
  if (players == nullptr)
  {
    std::cout << "no players in game." << '\n';
    return;
  }
  Card* temp;
  for (size_t i = 0; i < amountOfPlayers; i++)
  {
    std::cout << "Player: " << players[i]->get_name() << "s cards: " << '\n';
    temp = players[i]->get_hand();
    for (size_t j = 0; j < players[i]->get_amountOfCards(); j++)
    {
      std::cout << "Number: " << temp[j].number << "\tColor: " << temp[j].color << "\tFunction: "  << temp[j].function << '\n';
    }
  }
}


//Destructor
Board::~Board ()
{
  if (deck != nullptr)
  {
    delete [] deck;
    deck = nullptr;
  }
  for (size_t i = 0; i < amountOfPlayers; i++)
  {
    if (players[i] != nullptr)
    {
      delete players[i];
      players[i] = nullptr;
    }
  }
  if (players != nullptr)
  {
    delete [] players;
    players = nullptr;
  }
}
