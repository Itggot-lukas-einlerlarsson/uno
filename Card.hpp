#ifndef CARD_HPP
#define CARD_HPP

#include <string>

struct Card
{
  int number;
  std::string color;
  std::string function;
  Card();
  Card(int number, std::string color);
  Card(std::string function, std::string color);
};

#endif //CARD_HPP
